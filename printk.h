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
 * printk.h
 */
#ifndef __PRINTK_H__
#define __PRINTK_H__

#include <stdarg.h>
#include <stdlib.h>

/*
 * use the __attribute__ syntax to enable compiler warnings when the arguments
 * do not match the format string.
 */
#if defined __clang__
#  if __has_attribute(__format__)
#    define printk__format(fmt,arg)  __attribute__((__format__(__printf__,fmt,arg)))
#  endif
#elif defined __GNUC__
   // see also: https://ohse.de/uwe/articles/gcc-attributes.html
#  if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 3)
#    define printk__format(fmt,arg)  __attribute__((__format__(__printf__,fmt,arg)))
#  endif
#endif

#ifndef printk__format
#  define printk__format(fmt, arg) /* ignore */
#endif

extern int printk(const char *fmt, ...) printk__format(1, 2);
extern int fprintk(int fd, const char *fmt, ...) printk__format(2, 3);
extern int vprintk(const char *fmt, va_list ap);
extern int vfprintk(int fc, const char *fmt, va_list ap);


extern int snprintk(char *str, size_t size, const char *fmt, ...) printk__format(3, 4);
extern int sprintk(char *str, const char *fmt, ...) printk__format(2, 3);
extern int vsprintk(char *str, const char *fmt, va_list ap);
extern int vsnprintk(char *str, size_t size, const char *fmt, va_list ap);


#endif /* __PRINTK_H__ */
