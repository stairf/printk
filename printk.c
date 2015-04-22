/*****
 * Copyright (c) 2015, Stefan Reif
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****/

/*
 * printk.c
 *
 * This file contains a simple implementation of the standard C function
 * printf, renamed to printk because of some incompatibilities. It supports the
 * following features:
 *   - flags `#', `0', `-', ` ' (space), and `+'
 *   - width specifications, both numeric and `*'
 *   - precision specifications, both numeric and `*'
 *   - conversions `d', `i', `u', `x', `X', and `o', all combined with legth specifiers `l', `ll', `h', `hh', `j', `z', and `t'
 *   - conversions `c' and `s'
 *   - conversions `n', `ln', and `lln'
 *
 * This printf implementation is not the fastest one, not the smallest one, and
 * it lacks some features requried by POSIX such as floating point arguments
 * and argument indexing using $. However, it aims to be portable and
 * reentrant, and to minimize library dependencies.
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>

#include "printk.h"

/*
 * printk configuration:
 *  - WRITE_BUFSZ : output buffer size, on stack
 *  - FD          : the default file descriptor used by printk/vprintk
 */
#define WRITE_BUFSZ 1024
#define FD          1
#define INVAL_FD    (-1)

/*
 * simple libc re-implementation
 *
 * re-implement basic libc functions to avoid library dependencies, and to
 * ensure that these functions are reentrant.
 */

#define strlen my_strlen
static inline size_t my_strlen(const char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	return i;
}

#define strnlen my_strnlen
static inline size_t my_strnlen(const char *s, size_t n)
{
	size_t i = 0;
	while (s[i] && i < n)
		i++;
	return i;
}

#define memcpy my_memcpy
static inline void *my_memcpy(void *dest, const void *src, size_t n)
{
	char *d = (char *) dest;
	char *s = (char *) src;
	for (size_t i = 0; i < n; ++i)
		d[i] = s[i];
	return (void*) dest;
}

#define strchr my_strchr
static inline char *my_strchr(const char *s, int c)
{
	char search = (char) (unsigned char) c;
	while (1) {
		if (*s == search)
			return (char *) s;
		else if (!*s)
			return NULL;
		s++;
	}
}

#define isdigit my_isdigit
static inline int my_isdigit(int c)
{
	return '0' <= c && c <= '9';
}


// define format flag bits
#define FLAG_ALTERNATIVE   0x0001 // '#' flag
#define FLAG_ZERO          0x0002 // '0' flag
#define FLAG_DASH          0x0004 // '-' flag
#define FLAG_SPACE         0x0008 // ' ' flag
#define FLAG_PLUS          0x0010 // '+' flag
#define FLAG_UC            0x0020 // uppercase conversion
#define FLAG_WIDTH         0x0040 // width specified
#define FLAG_PREC          0x0080 // precision specified
#define FLAG_NUMERIC       0x0100 // numeric conversion

// define buffer flag bits
#define BUF_ERROR          0x01

// internal data structure for an output buffer
typedef struct buf {
	char *data;
	size_t size;
	size_t idx;
	size_t written;
	int flags;
	int fd;
} buf_t;

// flush the local buffer
static inline void flush(buf_t *buf)
{
	if (buf->fd >= 0 && !(buf->flags & BUF_ERROR)) {
		if (buf->idx && (write(buf->fd, buf->data, buf->idx) < 0))
			buf->flags |= BUF_ERROR;
		buf->idx = 0;
	}
	buf->written += buf->idx;
}

// write multiple characters to the buffer
static inline void pushall(buf_t *buf, const char *begin, size_t n)
{
	size_t avail = buf->size - buf->idx;
	size_t min;
	if (n < avail) {
		memcpy(buf->data + buf->idx, begin, n);
		buf->idx += n;
		return;
	}

	while (n > 0) {
		avail = buf->size - buf->idx;
		if (!avail) {
			flush(buf);
			avail = buf->size - buf->idx;
			if (!avail)
				return;
		}
		min = (avail < n) ? avail : n;
		memcpy(buf->data + buf->idx, begin, min);
		n -= min;
		buf->idx += min;
		begin += min;
	}
}

// write one char to the buffer
static inline void push(buf_t *buf, char x)
{
	pushall(buf, &x, 1);
}


// digits for both lower and upper case conversions
static const char digits_lc[] = "0123456789abcdef";
static const char digits_uc[] = "0123456789ABCDEF";

// parse a number, similar to strtol
static int parse_num(const char *start, char **endptr)
{
	int val = 0;
	const char *digits = digits_lc;
	while (isdigit(*start)) {
		val *= 10;
		val += strchr(digits, *start) - digits;
		start++;
	}
	*endptr = (char *) start;
	return val;
}

// normalize conversion flags
static inline int normalize_flags(int flags)
{
	// if both dash and zero flags appear, the zero flag is ignored
	if (flags & FLAG_DASH)
		flags &= ~FLAG_ZERO;

	// a plus overrides a space if both are used
	if (flags & FLAG_PLUS)
		flags &= ~FLAG_SPACE;

	// if a precision is given for a numeric conversion, the zero flag is
	// ignored
	if ((flags & FLAG_NUMERIC) && (flags & FLAG_PREC))
		flags &= ~FLAG_ZERO;
	return flags;
}

// convert the remainder to a digit
#define rem2digit(rem,uc) (uc ? digits_uc[rem] : digits_lc[rem])


/*
 * generic conversion function implementation
 *
 * The function performs multiple steps to convert a number to a string:
 *   1. write the (reversed) number represenatation into a local buffer, by
 *      iteratively dividing the number by the base.
 *   2. check the number length and figure out how many fill characters are
 *      required to achive the required fields width.
 *   3. write out the fill chars, the alternative prefix, the sign char, and
 *      the number that is stored in the local buffer to the output buffer.
 */
#define FMT_FUNCTION(fmt,SIGNED,BASE,type,utype,ALTPFX,EXTRAFLAGS) \
	static void format_ ##fmt (buf_t *buf, type val, int flags, int width, int prec) \
	{ \
		/* normalize the flags, and apply the default precision */ \
		flags = normalize_flags(flags | EXTRAFLAGS); \
		if (!(flags & FLAG_PREC)) \
			prec = 1; \
		\
		/* get a local number buffer */ \
		char numbuf[sizeof(type) * CHAR_BIT + 1]; \
		char *ptr = numbuf; \
		utype u = (utype) val; \
		/* handle negative values */ \
		int negative = 0; \
		char fill_char = (flags & FLAG_ZERO) ? '0' : ' '; \
		if (SIGNED && (val < 0)) { \
			negative = 1; \
			u = -val; \
		} \
		/* handle 0 values */ \
		if (!u) { \
			if (prec) \
				*ptr++ = '0'; \
			if (flags & FLAG_ALTERNATIVE) \
				flags &= ~FLAG_ALTERNATIVE; \
		} \
		/* write the number into the local buffer, reversed */ \
		while (u) { \
			utype div = u / BASE; \
			utype rem = u % BASE; \
			*ptr++ = rem2digit(rem, (flags & FLAG_UC)); \
			u = div; \
		} \
		/* numbuf now contains the reversed representation of val */ \
		int numlen = ptr - numbuf; \
		/* fill how many bytes to achive width? */ \
		int nfill = 0; \
		if (flags & FLAG_WIDTH) { \
			nfill = (width - numlen); \
			if ((flags & FLAG_PREC) && numlen < prec) \
				nfill = width - prec; \
			if (flags & FLAG_ALTERNATIVE) \
				nfill -= strlen(ALTPFX); \
			if (negative || (flags & FLAG_SPACE) || (flags & FLAG_PLUS)) \
				nfill--; \
			if (nfill < 0) \
				nfill = 0; \
		} \
		/* emit trailing spaces */ \
		if (!(flags & FLAG_DASH) && !(flags & FLAG_ZERO)) { \
			for (int i = 0; i < nfill; ++i) \
				push(buf, fill_char); \
			nfill = 0; \
		} \
		/* print sign char */ \
		if (negative) \
			push(buf, '-'); \
		else if (flags & FLAG_SPACE) \
			push(buf, ' '); \
		else if (flags & FLAG_PLUS) \
			push(buf, '+'); \
		\
		/* print alternative prefix */ \
		if ((flags & FLAG_ALTERNATIVE) && (BASE != 8 || (numlen >= prec))) \
			pushall(buf, ALTPFX, strlen(ALTPFX)); \
		\
		if (flags & FLAG_ZERO) { \
			/* when the padding character is '0', it must be applied _after_ */ \
			/* the sign char or the alternative prefix                       */ \
			for (int i = 0; i < nfill; ++i) \
				push(buf, fill_char); \
			nfill = 0; \
		} \
		/* write '0' chars to achieve the required precision */ \
		if (prec > numlen) { \
			for (int i = numlen; i < prec; ++i) \
				push(buf, '0'); \
		} \
		/* copy the number from the local buffer to the ouput buffer */ \
		ptr--; \
		while (ptr >= numbuf) \
			push(buf, *ptr--); \
		\
		/* write the remaining fill chars, if required */ \
		for (int i = 0; i < nfill; ++i) \
			push(buf, fill_char); \
	}


FMT_FUNCTION(jd, 1, 10, intmax_t, uintmax_t, "",   FLAG_NUMERIC)
FMT_FUNCTION(ju, 0, 10, intmax_t, uintmax_t, "",   FLAG_NUMERIC)
FMT_FUNCTION(jx, 0, 16, intmax_t, uintmax_t, "0x", FLAG_NUMERIC)
FMT_FUNCTION(jX, 0, 16, intmax_t, uintmax_t, "0X", FLAG_NUMERIC | FLAG_UC)
FMT_FUNCTION(jo, 0,  8, intmax_t, uintmax_t, "0",  FLAG_NUMERIC)

// hack: this is a very simple way to handle pointers ...
FMT_FUNCTION(p,  0, 16, intptr_t, uintptr_t, "0x", FLAG_ALTERNATIVE)

/*
 * most format_* functions are just very small inline wrappers. The compiler
 * will optimize them out so that only the intmax_t versions remain.
 */
#define WRAP(name,type,target) \
	static inline void format_ ## name (buf_t *buf, type val, int flags, int width, int prec) \
	{ \
		format_ ## target (buf, val, flags, width, prec); \
	} \

WRAP(d, int, jd)
WRAP(u, unsigned int, ju)
WRAP(x, unsigned int, jx)
WRAP(X, unsigned int, jX)
WRAP(o, unsigned int, jo)

WRAP(ld, long, jd)
WRAP(lu, unsigned long, ju)
WRAP(lx, unsigned long, jx)
WRAP(lX, unsigned long, jX)
WRAP(lo, unsigned long, jo)

WRAP(lld, long long, jd)
WRAP(llu, unsigned long long, ju)
WRAP(llx, unsigned long long, jx)
WRAP(llX, unsigned long long, jX)
WRAP(llo, unsigned long long, jo)

WRAP(zd, ssize_t, jd)
WRAP(zu, size_t, ju)
WRAP(zx, size_t, jx)
WRAP(zX, size_t, jX)
WRAP(zo, size_t, jo)

/*
 * no unsigned ptrdiff_t exists, but the conversion to uintmax_t produces the
 * correct result.
 */
WRAP(td, ptrdiff_t, jd)
WRAP(tu, ptrdiff_t, ju)
WRAP(tx, ptrdiff_t, jx)
WRAP(tX, ptrdiff_t, jX)
WRAP(to, ptrdiff_t, jo)

// write a string to the output buffer
static void format_s(buf_t *buf, const char *val, int flags, int width, int prec)
{
	if (!val)
		val = "(null)";

	size_t len = (flags & FLAG_PREC) ? strnlen(val, prec) : strlen(val);
	int nfill = 0;
	if ((flags & FLAG_WIDTH) && (size_t) width > len) {
		nfill = width - len;
	}
	if (!(flags & FLAG_DASH)) {
		for (int i = 0; i < nfill; ++i)
			push(buf, ' ');
		nfill = 0;
	}
	pushall(buf, val, len);
	for (int i = 0; i < nfill; ++i) {
		push(buf, ' ');
	}
}

// write one character to the output buffer
static void format_c(buf_t *buf, int val, int flags, int width, int prec)
{
	unsigned char uc = (unsigned char) val;

	int nfill = 0;
	if ((flags & FLAG_WIDTH) && (size_t) width > 1) {
		nfill = width - 1;
	}
	if (!(flags & FLAG_DASH)) {
		for (int i = 0; i < nfill; ++i)
			push(buf, ' ');
		nfill = 0;
	}
	push(buf, uc);
	for (int i = 0; i < nfill; ++i) {
		push(buf, ' ');
	}

	// ignore unused parameter
	(void) prec;
}

// handle %n conversions
static void format_n(buf_t *buf, int *val, int flags, int width, int prec)
{
	size_t written = buf->written;
	*val = (int) written;

	// ignore unused parameters
	(void) flags;
	(void) width;
	(void) prec;
}

// handle %ln conversions
static void format_ln(buf_t *buf, long int *val, int flags, int width, int prec)
{
	size_t written = buf->written;
	*val = (long int) written;

	// ignore unused parameters
	(void) flags;
	(void) width;
	(void) prec;
}

// handle %lln conversions
static void format_lln(buf_t *buf, long long int *val, int flags, int width, int prec)
{
	size_t written = buf->written;
	*val = (long long int) written;

	// ignore unused parameters
	(void) flags;
	(void) width;
	(void) prec;
}

// implicitly pass buf, flags, width, and prec to the format functions
#define convert(format_func,type) do { \
		format_func(buf, va_arg(ap, type), flags, width, prec); \
	} while (0)

// the ``format'' function does all the work
static inline int format(buf_t *buf, const char *restrict fmt, va_list ap)
{
	char *nextspec;
	size_t len;

	while (*fmt) {
		if (*fmt == '%') {
			// parse format specification
			fmt++;
			int flags = 0;
			int prec = 0;
			int width = 0;

			// parse flags
			while (1) {
				if (*fmt == '#')
					flags |= FLAG_ALTERNATIVE;
				else if (*fmt == '0')
					flags |= FLAG_ZERO;
				else if (*fmt == '-')
					flags |= FLAG_DASH;
				else if (*fmt == ' ')
					flags |= FLAG_SPACE;
				else if (*fmt == '+')
					flags |= FLAG_PLUS;
				else
					break;
				fmt++;
			}

			// parse width
			if (isdigit(*fmt)) {
				char *endptr;
				width = parse_num(fmt, &endptr);
				fmt = endptr;
				flags |= FLAG_WIDTH;
			} else if ('*' == *fmt) {
				fmt++;
				width = va_arg(ap, int);
				if (width < 0) {
					flags |= FLAG_DASH;
					width = -width;
				}
				flags |= FLAG_WIDTH;
			}

			// parse prec
			if (*fmt == '.') {
				fmt++;
				flags |= FLAG_PREC;
				if (isdigit(*fmt)) {
					char *endptr;
					prec = parse_num(fmt, &endptr);
					fmt = endptr;
				} else if ('*' == *fmt) {
					fmt++;
					prec = va_arg(ap, int);
					if (prec < 0)
						prec = 0;
				}
			}

			// everything smaller than int is converted to int -> ignore %h and
			// %hh here
			if (*fmt == 'h')
				fmt++;
			if (*fmt == 'h')
				fmt++;

			// now comes either the conversion char or the length specification
			if (*fmt == 'd' || *fmt == 'i') {
				convert(format_d, int);
			} else if (*fmt == 'u') {
				convert(format_u, int);
			} else if (*fmt == 'x') {
				convert(format_x, int);
			} else if (*fmt == 'X') {
				convert(format_X, int);
			} else if (*fmt == 'o') {
				convert(format_o, int);
			} else if (*fmt == 'p') {
				convert(format_p, intptr_t);
			} else if (*fmt == 's') {
				convert(format_s, char *);
			} else if (*fmt == 'c') {
				convert(format_c, int);
			} else if (*fmt == 'n') {
				convert(format_n, int *);
			} else if (*fmt == 'z') {
				// %z conversions
				fmt++;
				if (*fmt == 'd' || *fmt == 'i') {
					convert(format_zd, ssize_t);
				} else if (*fmt == 'u') {
					convert(format_zu, ssize_t);
				} else if (*fmt == 'x') {
					convert(format_zx, ssize_t);
				} else if (*fmt == 'X') {
					convert(format_zX, ssize_t);
				} else if (*fmt == 'o') {
					convert(format_zo, ssize_t);
				}
			} else if (*fmt == 't') {
				// %t conversions
				fmt++;
				if (*fmt == 'd' || *fmt == 'i') {
					convert(format_td, ssize_t);
				} else if (*fmt == 'u') {
					convert(format_tu, ssize_t);
				} else if (*fmt == 'x') {
					convert(format_tx, ssize_t);
				} else if (*fmt == 'X') {
					convert(format_tX, ssize_t);
				} else if (*fmt == 'o') {
					convert(format_to, ssize_t);
				}
			} else if (*fmt == 'j') {
				// %j conversions
				fmt++;
				if (*fmt == 'd' || *fmt == 'i') {
					convert(format_jd, intmax_t);
				} else if (*fmt == 'u') {
					convert(format_ju, intmax_t);
				} else if (*fmt == 'x') {
					convert(format_jx, intmax_t);
				} else if (*fmt == 'X') {
					convert(format_jX, intmax_t);
				} else if (*fmt == 'o') {
					convert(format_jo, intmax_t);
				}
			} else if (*fmt == 'l') {
				// %l conversions
				fmt++;
				if (*fmt == 'd' || *fmt == 'i') {
					convert(format_ld, long);
				} else if (*fmt == 'u') {
					convert(format_lu, long);
				} else if (*fmt == 'x') {
					convert(format_lx, long);
				} else if (*fmt == 'X') {
					convert(format_lX, long);
				} else if (*fmt == 'o') {
					convert(format_lo, long);
				} else if (*fmt == 'n') {
					convert(format_ln, long int *);
				} else if( *fmt == 'l' ) {
					 // %ll conversions
					fmt++;
					if (*fmt == 'd' || *fmt == 'i') {
						convert(format_lld, long long);
					} else if (*fmt == 'u') {
						convert(format_llu, long long);
					} else if (*fmt == 'x') {
						convert(format_llx, long long);
					} else if (*fmt == 'X') {
						convert(format_llX, long long);
					} else if (*fmt == 'o') {
						convert(format_llo, long long);
					} else if (*fmt == 'n') {
						convert(format_lln, long long int *);
					}
				}
			} else {
				// %% conversion
				push(buf, '%');
			}
			// skip last char of format specification
			fmt++;
		}
		// write all characters until the next '%' char
		nextspec = strchr(fmt, '%');
		if (!nextspec)
			len = strlen(fmt);
		else
			len = nextspec - fmt;
		if (len) {
			pushall(buf, fmt, len);
			fmt += len;
		}
	}

	flush(buf);
	if (buf->flags & BUF_ERROR)
		return -1;
	if (buf->written > INT_MAX)
		return INT_MAX;
	return (int) buf->written;
}

int vfprintk(int fd, const char *restrict fmt, va_list ap)
{
	// vfprintk ist the standard function for everything that writes to a file
	char buf_data[WRITE_BUFSZ];
	buf_t fmtbuf = {
		.data = buf_data,
		.size = sizeof(buf_data),
		.idx = 0,
		.written = 0,
		.flags = 0,
		.fd = fd
	};
	return format(&fmtbuf, fmt, ap);
}

int vprintk(const char *restrict fmt, va_list ap)
{
	return vfprintk(FD, fmt, ap);
}

int fprintk(int fd, const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int result = vfprintk(fd, fmt, ap);
	va_end(ap);
	return result;
}


int printk(const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int result = vfprintk(FD, fmt, ap);
	va_end(ap);
	return result;
}

int vsnprintk(char *restrict str, size_t size, const char *restrict fmt, va_list ap)
{
	buf_t fmtbuf = {
		.data = str,
		.size = size,
		.idx = 0,
		.written = 0,
		.flags = 0,
		.fd = INVAL_FD
	};
	int res = format(&fmtbuf, fmt, ap);
	if (res < 0)
		return res;
	// add null byte
	size_t written = fmtbuf.written;
	if (written >= size) {
		if (size)
			str[size - 1] = '\0';
	} else {
		str[written] = '\0';
	}
	return res;
}

int vsprintk(char *restrict str, const char *restrict fmt, va_list ap)
{
	return vsnprintk(str, SIZE_MAX, fmt, ap);
}

int snprintk(char *restrict str, size_t size, const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int result = vsnprintk(str, size, fmt, ap);
	va_end(ap);
	return result;
}

int sprintk(char *restrict str, const char *restrict fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int result = vsnprintk(str, SIZE_MAX, fmt, ap);
	va_end(ap);
	return result;
}

