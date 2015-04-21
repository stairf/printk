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
 * enable checks that raise warnings about ignored parameters, because these
 * warnings are disabled explicitly in the Makefile
 */
#define IGNORED

/* no conversion */
printf("");
printf("\n");
printf("hello\n");
printf(" \n");

/* %% conversion */
printf("%%\n");
printf("%%%%\n");
printf("100%% sure\n");
printf("%% test %% text %%\n");

/* %d conversion */
printf("%d\n", 0);
printf("%d\n", 1);
printf("%d\n", 2);
printf("%d\n", 10);
printf("%d\n", -1);
printf("%d\n", -12345);
printf("%d\n", INT_MAX);
printf("%d\n", INT_MIN);
printf("%d+%d=%d\n", 1, 2, 3);
printf("%d+%d=%d\n", -1, 234, 233);

/* %i conversion */
printf("%i\n", 0);
printf("%i\n", 1);
printf("%i\n", 123);
printf("%i\n", -1);
printf("%i\n", -17);
printf("%i\n", INT_MAX);
printf("%i\n", INT_MIN);
printf("%i+%i=%i\n", 1, 2, 3);
printf("%i+%i=%i\n", -1, 234, 233);

/* %u conversion */
printf("%u\n", 0);
printf("%u\n", 1);
printf("%u\n", INT_MAX);
printf("%u\n", UINT_MAX);
printf("%u+%u=%u\n", 1, 2, 3);

/* %ld conversion */
printf("%ldx%ldy%ld\n", 0L, 1L, 123L);
printf("%ld %ld %ld %ld\n", LONG_MIN, LONG_MAX, -1L, -123L);

/* %lu conversion */
printf("%lu %lu %lu\n", 0L, 123L, ULONG_MAX);

/* %lx conversion */
printf("lx: %lx %lx %lx %lx %lx\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);

/* lX conversion */
printf("lX: %lX %lX %lX %lX %lX\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);

/* lo conversion */
printf("lo: %lo %lo %lo %lo %lo\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);

/* lld conversion */
printf("lld: %lld %lld %lld %lld %lld\n", 0LL, 1LL, 2345LL, LLONG_MIN, LLONG_MAX);

/* lli conversion */
printf("lli: %lli %lli %lli %lli %lli\n", 0LL, 1LL, 2345LL, LLONG_MIN, LLONG_MAX);

/* llx conversion */
printf("llx: %llx %llx %llx %llx %llx\n", 0LL, 1LL, 567LL, LLONG_MAX, ULLONG_MAX);

/* llX conversion */
printf("llX: %llX %llX %llX %llX %llX\n", 0LL, 1LL, 567LL, LLONG_MAX, ULLONG_MAX);

/* llo conversion */
printf("llo: %llo %llo %llo %llo %llo\n", 0LL, 1LL, 567LL, LLONG_MAX, ULLONG_MAX);

/* llu conversion */
printf("llu: %llu %llu %llu %llu %llu\n", 0LL, 1LL, 567LL, LLONG_MAX, ULLONG_MAX);

/* zd conversion */
printf("zd: %zd %zd %zd %zd %zd\n", (ssize_t) 0, (ssize_t) -1, (ssize_t) 123, (size_t) -SSIZE_MAX, (size_t) SSIZE_MAX);

/* zi conversion */
printf("zi: %zi %zi %zi %zi %zi\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) 123, (size_t) -SSIZE_MAX, (size_t) SSIZE_MAX);

/* zu conversion */
printf("zu: %zu %zu %zu %zu\n", (size_t) 0, (size_t) 1, (size_t) 678, (size_t) SIZE_MAX);

/* zx conversion */
printf("zx: %zx %zx %zx %zx\n", (size_t) 0, (size_t) 1, (size_t) 678, (size_t) SIZE_MAX);

/* zX conversion */
printf("zX: %zX %zX %zX %zX\n", (size_t) 0, (size_t) 1, (size_t) 678, (size_t) SIZE_MAX);

/* zo conversion */
printf("zo: %zo %zo %zo %zo\n", (size_t) 0, (size_t) 1, (size_t) 678, (size_t) SIZE_MAX);

/* jd conversion */
printf("jd: %jd %jd %jd %jd %jd\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MIN, (intmax_t) INTMAX_MAX);

/* ji conversion */
printf("ji: %ji %ji %ji %ji %ji\n", (intmax_t) 0, (intmax_t) -1, (intmax_t) 123, (intmax_t) INTMAX_MIN, (intmax_t) INTMAX_MAX);

/* ju conversion */
printf("ju: %ju %ju %ju %ju\n", (uintmax_t) 0, (uintmax_t) 1, (uintmax_t) 678, (uintmax_t) INTMAX_MAX);

/* jx conversion */
printf("jx: %jx %jx %jx %jx\n", (uintmax_t) 0, (uintmax_t) 1, (uintmax_t) 678, (uintmax_t) INTMAX_MAX);

/* jX conversion */
printf("jX: %jX %jX %jX %jX\n", (uintmax_t) 0, (uintmax_t) 1, (uintmax_t) 678, (uintmax_t) INTMAX_MAX);

/* jo conversion */
printf("jo: %jo %jo %jo %jo\n", (uintmax_t) 0, (uintmax_t) 1, (uintmax_t) 678, (uintmax_t) INTMAX_MAX);

/* td conversion */
printf("td: %td %td %td %td %td\n", (ptrdiff_t) 0, (ptrdiff_t) -1, (ptrdiff_t) 123, (ptrdiff_t) PTRDIFF_MIN, (ptrdiff_t) PTRDIFF_MAX);

/* ti conversion */
printf("ti: %ti %ti %ti %ti %ti\n", (ptrdiff_t) 0, (ptrdiff_t) -1, (ptrdiff_t) 123, (ptrdiff_t) PTRDIFF_MIN, (ptrdiff_t) PTRDIFF_MAX);

/* tu conversion */
printf("tu: %tu %tu %tu %tu\n", (ptrdiff_t) 0, (ptrdiff_t) 1, (ptrdiff_t) 678, (ptrdiff_t) PTRDIFF_MAX);

/* tx conversion */
printf("tx: %tx %tx %tx %tx\n", (ptrdiff_t) 0, (ptrdiff_t) 1, (ptrdiff_t) 678, (ptrdiff_t) PTRDIFF_MAX);

/* tX conversion */
printf("tX: %tX %tX %tX %tX\n", (ptrdiff_t) 0, (ptrdiff_t) 1, (ptrdiff_t) 678, (ptrdiff_t) PTRDIFF_MAX);

/* to conversion */
printf("to: %to %to %to %to\n", (ptrdiff_t) 0, (ptrdiff_t) 1, (ptrdiff_t) 678, (ptrdiff_t) PTRDIFF_MAX);

/* %s conversion */
printf("s: %s\n", "hello");
printf("s: he%so\n", "ll");
printf("s: %s%s%s%s", "fo", "ob", "ar", "\n");

printf("s+w:%1s %2s %10s\n", "", "hello", "world");
printf("s+w+dash:%-1s %-2s %-10s\n", "", "hello", "world");
printf("s+p:%.1s %.2s %.10s\n", "", "hello", "world");
printf("s+p+dash:%-.1s %-.2s %-.10s\n", "", "hello", "world");
printf("s+w+p:%1.0s %1.3s %3.1s %4.10s %2.10s\n", "hello", "world", "foobar", "foo", "bar");
printf("s+w+p+dash:%-1.0s %-1.3s %-3.1s %-4.10s %-2.10s\n", "hello", "world", "foobar", "foo", "bar");

/* %p conversion */
printf("p:%p\n", (void*)0x1);
printf("p: %p %p %p\n", (void*)0x1, (void*) 0x02, (void*)UINT_MAX);
printf("p: %p\n", (void *)-1);

/* width */
printf("w: %10s\n", "hello");
printf("w: %5d%6i\n", INT_MAX, INT_MIN);
printf("w: %2X\n", 0);
printf("w: %2x %2x\n", INT_MAX, UINT_MAX);
printf("w: %*d %*x\n", 4, -1, 123, UINT_MAX);
printf("w: %1u %10u %17u %2u\n", 1, 0, UINT_MAX, UINT_MAX);

/* negative width */
printf("w<0: %*d\n", -5, 3);
printf("w<0: %-*X %*x\n", -13, 0xF00, -2, 0xF00BAA);
printf("w<0: %#-*X %#*o\n", -1, 0xBAADF00D, -2, UINT_MAX);

/* precision */
printf("p: %.d\n", 0);
printf("p: %.0d\n", 0);
printf("p: %.1d %.12i\n", INT_MAX, INT_MIN);
printf("p: %.0x %.0x %.0X\n", 0, 1, UINT_MAX);
printf("p: %.2s\n", "hello");
printf("p: %.15s %.1000s\n", "hello", "world");

/* width & precision */
printf("w+p: %5.2d\n", 3);
printf("w+p: %7.3d %4.5d %8.2i\n", 12, 13, -1);
printf("w+p: %*.7d %8.*u\n", 10, 0, 5, 1);
printf("w+p: %*.*x\n", 15, 10, 0x5);

/* alt flag */
printf("alt: %#x %#x %#x %#x %#x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("alt: %#X %#X %#X %#X %#X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("alt: %#o %#o %#o %#o %#o\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("alt: %#lx %#lx %#lx %#lx %#lx\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("alt: %#lX %#lX %#lX %#lX %#lX\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("alt: %#lo %#lo %#lo %#lo %#lo\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("alt: %#llx %#llx %#llx %#llx %#llx\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("alt: %#llX %#llX %#llX %#llX %#llX\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("alt: %#llo %#llo %#llo %#llo %#llo\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("alt: %#zx %#zx %#zx %#zx\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("alt: %#zX %#zX %#zX %#zX\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("alt: %#zo %#zo %#zo %#zo\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("alt: %#jx %#jx %#jx %#jx\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX);
printf("alt: %#jX %#jX %#jX %#jX\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX);
printf("alt: %#jo %#jo %#jo %#jo\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX);

/* dash flag */
printf("dash: %-d %-d %-d %-d %-d %-d %-d\n", 0, 1, -1, -123, 123, INT_MAX, INT_MIN);
printf("dash: %-i %-i %-i %-i %-i %-i %-i\n", 0, 1, -1, -123, 123, INT_MAX, INT_MIN);
printf("dash: %-x %-x %-x %-x %-x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("dash: %-X %-X %-X %-X %-X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("dash: %-o %-o %-o %-o %-o\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("dash: %-u %-u %-u %-u %-u\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("dash: %-ld %-ld %-ld %-ld %-ld %-ld %-ld\n", 0L, 1L, -1L, -123L, 123L, LONG_MAX, LONG_MIN);
printf("dash: %-li %-li %-li %-li %-li %-li %-li\n", 0L, 1L, -1L, -123L, 123L, LONG_MAX, LONG_MIN);
printf("dash: %-lx %-lx %-lx %-lx %-lx\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("dash: %-lX %-lX %-lX %-lX %-lX\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("dash: %-lo %-lo %-lo %-lo %-lo\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("dash: %-lu %-lu %-lu %-lu %-lu\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("dash: %-lld %-lld %-lld %-lld %-lld %-lld %-lld\n", 0LL, 1LL, -1LL, -123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("dash: %-lli %-lli %-lli %-lli %-lli %-lli %-lli\n", 0LL, 1LL, -1LL, -123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("dash: %-llx %-llx %-llx %-llx %-llx\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("dash: %-llX %-llX %-llX %-llX %-llX\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("dash: %-llo %-llo %-llo %-llo %-llo\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("dash: %-llu %-llu %-llu %-llu %-llu\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("dash: %-zd %-zd %-zd %-zd %-zd\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) -123, (ssize_t) 123);
printf("dash: %-zi %-zi %-zi %-zi %-zi\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) -123, (ssize_t) 123);
printf("dash: %-zx %-zx %-zx %-zx\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("dash: %-zX %-zX %-zX %-zX\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("dash: %-zo %-zo %-zo %-zo\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("dash: %-zu %-zu %-zu %-zu\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("dash: %-jd %-jd %-jd %-jd %-jd %-jd %-jd\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) -123, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) INTMAX_MIN) ;
printf("dash: %-ji %-ji %-ji %-ji %-ji %-ji %-ji\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) -123, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) INTMAX_MIN) ;
printf("dash: %-jx %-jx %-jx %-jx %-jx\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX) ;
printf("dash: %-jX %-jX %-jX %-jX %-jX\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX) ;
printf("dash: %-jo %-jo %-jo %-jo %-jo\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX) ;
printf("dash: %-ju %-ju %-ju %-ju %-ju\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX) ;

/* zero flag */
printf("zero: %0d %0d %0d %0d %0d %0d %0d\n", 0, 1, -1, -123, 123, INT_MAX, INT_MIN);
printf("zero: %0i %0i %0i %0i %0i %0i %0i\n", 0, 1, -1, -123, 123, INT_MAX, INT_MIN);
printf("zero: %0x %0x %0x %0x %0x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("zero: %0X %0X %0X %0X %0X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("zero: %0o %0o %0o %0o %0o\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("zero: %0u %0u %0u %0u %0u\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("zero: %0ld %0ld %0ld %0ld %0ld %0ld %0ld\n", 0L, 1L, -1L, -123L, 123L, LONG_MAX, LONG_MIN);
printf("zero: %0li %0li %0li %0li %0li %0li %0li\n", 0L, 1L, -1L, -123L, 123L, LONG_MAX, LONG_MIN);
printf("zero: %0lx %0lx %0lx %0lx %0lx\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("zero: %0lX %0lX %0lX %0lX %0lX\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("zero: %0lo %0lo %0lo %0lo %0lo\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("zero: %0lu %0lu %0lu %0lu %0lu\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("zero: %0lld %0lld %0lld %0lld %0lld %0lld %0lld\n", 0LL, 1LL, -1LL, -123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("zero: %0lli %0lli %0lli %0lli %0lli %0lli %0lli\n", 0LL, 1LL, -1LL, -123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("zero: %0llx %0llx %0llx %0llx %0llx\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("zero: %0llX %0llX %0llX %0llX %0llX\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("zero: %0llo %0llo %0llo %0llo %0llo\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("zero: %0llu %0llu %0llu %0llu %0llu\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("zero: %0zd %0zd %0zd %0zd %0zd\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) -123, (ssize_t) 123);
printf("zero: %0zi %0zi %0zi %0zi %0zi\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) -123, (ssize_t) 123);
printf("zero: %0zx %0zx %0zx %0zx\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("zero: %0zX %0zX %0zX %0zX\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("zero: %0zo %0zo %0zo %0zo\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("zero: %0zu %0zu %0zu %0zu\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("zero: %0jd %0jd %0jd %0jd %0jd %0jd %0jd\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) -123, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) INTMAX_MIN) ;
printf("zero: %0ji %0ji %0ji %0ji %0ji %0ji %0ji\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) -123, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) INTMAX_MIN) ;
printf("zero: %0jx %0jx %0jx %0jx %0jx\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX);
printf("zero: %0jX %0jX %0jX %0jX %0jX\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX);
printf("zero: %0jo %0jo %0jo %0jo %0jo\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX);
printf("zero: %0ju %0ju %0ju %0ju %0ju\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, (intmax_t) INTMAX_MAX, (intmax_t) UINTMAX_MAX);

/* space flag */
printf("space: % d % d % d % d % d % d % d\n", 0, 1, -1,  123, 123, INT_MAX, INT_MIN);
printf("space: % i % i % i % i % i % i % i\n", 0, 1, -1,  123, 123, INT_MAX, INT_MIN);
printf("space: % ld % ld % ld % ld % ld % ld % ld\n", 0L, 1L, -1L,  123L, 123L, LONG_MAX, LONG_MIN);
printf("space: % li % li % li % li % li % li % li\n", 0L, 1L, -1L,  123L, 123L, LONG_MAX, LONG_MIN);
printf("space: % lld % lld % lld % lld % lld % lld % lld\n", 0LL, 1LL, -1LL, 123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("space: % lli % lli % lli % lli % lli % lli % lli\n", 0LL, 1LL, -1LL, 123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("space: % zd % zd % zd % zd % zd\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) 123, (ssize_t) 123);
printf("space: % zi % zi % zi % zi % zi\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) 123, (ssize_t) 123);
printf("space: % jd % jd % jd % jd % jd % jd % jd\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) 123, (intmax_t) 123, INTMAX_MIN, INTMAX_MAX);
printf("space: % ji % ji % ji % ji % ji % ji % ji\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) 123, (intmax_t) 123, INTMAX_MIN, INTMAX_MAX);

/* plus flag */
printf("plus: %+d %+d %+d %+d %+d %+d %+d\n", 0, 1, -1, -123, 123, INT_MAX, INT_MIN);
printf("plus: %+i %+i %+i %+i %+i %+i %+i\n", 0, 1, -1, -123, 123, INT_MAX, INT_MIN);
printf("plus: %+ld %+ld %+ld %+ld %+ld %+ld %+ld\n", 0L, 1L, -1L,  123L, 123L, LONG_MAX, LONG_MIN);
printf("plus: %+li %+li %+li %+li %+li %+li %+li\n", 0L, 1L, -1L,  123L, 123L, LONG_MAX, LONG_MIN);
printf("plus: %+lld %+lld %+lld %+lld %+lld %+lld %+lld\n", 0LL, 1LL, -1LL, 123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("plus: %+lli %+lli %+lli %+lli %+lli %+lli %+lli\n", 0LL, 1LL, -1LL, 123LL, 123LL, LLONG_MAX, LLONG_MIN);
printf("plus: %+zd %+zd %+zd %+zd %+zd\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) 123, (ssize_t) 123);
printf("plus: %+zi %+zi %+zi %+zi %+zi\n", (ssize_t) 0, (ssize_t) 1, (ssize_t) -1, (ssize_t) 123, (ssize_t) 123);
printf("plus: %+jd %+jd %+jd %+jd %+jd %+jd %+jd\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) 123, (intmax_t) 123, INTMAX_MIN, INTMAX_MAX);
printf("plus: %+ji %+ji %+ji %+ji %+ji %+ji %+ji\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) -1, (intmax_t) 123, (intmax_t) 123, INTMAX_MIN, INTMAX_MAX);

/* width and alt flag */
printf("w+alt: %#4x %#5X %#17o\n", 1, INT_MAX, UINT_MAX);
printf("w+alt: %#2x %#5o %#5X\n", 0, 0, 0);
printf("w+alt: %#2x %#5o %#5X\n", INT_MAX, 1, 1);
printf("w+alt: %#2lx %#5lo %#5lX\n", LONG_MAX, 1L, 1L);
printf("w+alt: %#2llx %#5llo %#5llX\n", LLONG_MAX, 1LL, 1LL);
printf("w+alt: %#2zx %#5zo %#5zX\n", SIZE_MAX, (size_t) 1, (size_t)1);
printf("w+alt: %#2jx %#5jo %#5jX\n", INTMAX_MAX, (intmax_t) 1, (intmax_t)1);

/* width and zero flag */
printf("w+zero: %05d %06d %07d %08d %09d %010d %011d\n", 0, 1, 123, -1, -123, INT_MAX, INT_MIN);
printf("w+zero: %05i %06i %07i %08i %09i %010i %011i\n", 0, 1, 123, -1, -123, INT_MAX, INT_MIN);
printf("w+zero: %03x %04x %05x %06x %07x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+zero: %03X %04X %05X %06X %07X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+zero: %03o %04o %05o %06o %07o\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+zero: %03u %04u %05u %06u %07u\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+zero: %05ld %06ld %07ld %08ld %09ld %010ld %011ld\n", 0L, 1L, 123L, -1L, -123L, LONG_MAX, LONG_MIN);
printf("w+zero: %05li %06li %07li %08li %09li %010li %011li\n", 0L, 1L, 123L, -1L, -123L, LONG_MAX, LONG_MIN);
printf("w+zero: %03lx %04lx %05lx %06lx %07lx\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("w+zero: %03lX %04lX %05lX %06lX %07lX\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("w+zero: %03lo %04lo %05lo %06lo %07lo\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("w+zero: %03lu %04lu %05lu %06lu %07lu\n", 0L, 1L, 123L, LONG_MAX, ULONG_MAX);
printf("w+zero: %05lld %06lld %07lld %08lld %09lld %010lld %011lld\n", 0LL, 1LL, 123LL, -1LL, -123LL, LLONG_MAX, LLONG_MIN);
printf("w+zero: %05lli %06lli %07lli %08lli %09lli %010lli %011lli\n", 0LL, 1LL, 123LL, -1LL, -123LL, LLONG_MAX, LLONG_MIN);
printf("w+zero: %03llx %04llx %05llx %06llx %07llx\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("w+zero: %03llX %04llX %05llX %06llX %07llX\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("w+zero: %03llo %04llo %05llo %06llo %07llo\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("w+zero: %03llu %04llu %05llu %06llu %07llu\n", 0LL, 1LL, 123LL, LLONG_MAX, ULLONG_MAX);
printf("w+zero: %03zx %04zx %05zx %06zx\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("w+zero: %03zX %04zX %05zX %06zX\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("w+zero: %03zo %04zo %05zo %06zo\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("w+zero: %03zu %04zu %05zu %06zu\n", (size_t) 0, (size_t) 1, (size_t) 123, SIZE_MAX);
printf("w+zero: %03jx %04jx %05jx %06jx %07jx\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX, INTMAX_MIN);
printf("w+zero: %03jX %04jX %05jX %06jX %07jX\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX, INTMAX_MIN);
printf("w+zero: %03jo %04jo %05jo %06jo %07jo\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX, INTMAX_MIN);
printf("w+zero: %03ju %04ju %05ju %06ju %07ju\n", (intmax_t) 0, (intmax_t) 1, (intmax_t) 123, INTMAX_MAX, INTMAX_MIN);
printf("w+zero: %0*d %0*d %0*d\n", -1, 0, -1, 123, -12, 1);
printf("w+zero: %0*ld %0*ld %0*ld\n", -1, 0L, -1, 123L, -12, 1L);
printf("w+zero: %0*lld %0*lld %0*lld\n", -1, 0LL, -1, 123LL, -12, 1LL);
printf("w+zero: %0*zd %0*zd %0*zd\n", -1, (size_t) 0, -1, (size_t) 123, -12, (size_t) 1);
printf("w+zero: %0*jd %0*jd %0*jd\n", -1, (intmax_t) 0, -1, (intmax_t) 123, -12, (intmax_t) 1);

/* width and dash flag */
printf("w+dash: %-10d %-5x %-7u %-10p\n", 5, 0xfee, UINT_MAX, (void*)17);
printf("w+dash: %-*lu %-*x\n", 5, 3L, 7, 0x13);
printf("w+dash: %-*d %-*d %-*d %-*d %-*d\n", -1, 0, -1, 123, -10, 0, -10, 12, -10, INT_MAX);

/* width and space flag */
printf("p+space: % 5d % 6d % 7d % 8d % 9d % 10d % 11d\n", 0, 1, 123, -1, -123, INT_MAX, INT_MIN);
printf("p+space: % 5i % 6i % 7i % 8i % 9i % 10i % 11i\n", 0, 1, 123, -1, -123, INT_MAX, INT_MIN);
printf("p+space: % *d % *d % *d % *d % *d\n", -1, 0, -1, 123, -10, 0, -10, 12, -10, INT_MAX);

/* width and plus flag */
printf("p+plus: %+5d %+6d %+7d %+8d %+9d %+10d %+11d\n", 0, 1, 123, -1, -123, INT_MAX, INT_MIN);
printf("p+plus: %+5i %+6i %+7i %+8i %+9i %+10i %+11i\n", 0, 1, 123, -1, -123, INT_MAX, INT_MIN);
printf("p+plus: %+*d %+*d %+*d %+*d %+*d\n", -1, 0, -1, 123, -10, 0, -10, 12, -10, INT_MAX);

/* precision and alt flag */
printf("p+alt: %#.3x %#.4x %#.5x %#.6x %#.7x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("p+alt: %#.3X %#.4X %#.5X %#.6X %#.7X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("p+alt: %#.3o %#.4o %#.5o %#.6o %#.7o\n", 0, 1, 123, INT_MAX, UINT_MAX);

/* precision and zero flag */
#ifdef IGNORED
printf("p+zero: %0.3d %0.3d %0.3d %0.4d %0.5d %0.11d %0.12d\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX);
printf("p+zero: %0.3i %0.3i %0.3i %0.4i %0.5i %0.11i %0.12i\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX);
printf("p+zero: %0.3x %0.4x %0.5x %0.6x %0.7x\n", 0, 1, 123, INT_MAX, UINT_MAX);
#endif /* IGNORED */

/* precision and dash flag */
printf("p+dash: %-.3d %-.3d %-.4d %-.5d %-.6d, %-.11d %-.12d\n", 0, 1, 123, -123, INT_MIN, INT_MAX, 1);
printf("p+dash: %-.3i %-.3i %-.4i %-.5i %-.6i, %-.11i %-.12i\n", 0, 1, 123, -123, INT_MIN, INT_MAX, 1);
printf("p+dash: %-.3x %-.4x %-.5x %-.6x %-.12x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("p+dash: %-.3X %-.4X %-.5X %-.6X %-.12X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("p+dash: %-.3o %-.4o %-.5o %-.6o %-.12o\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("p+dash: %-.3u %-.4u %-.5u %-.6u %-.12u\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("p+dash: %-.*d %-.*d %-.*d %-.*d %-.*d\n", 0, 0, 0, 1, 1, INT_MAX, 10, 1, 10, INT_MIN);
printf("p+dash: %-.*i %-.*i %-.*i %-.*i %-.*i\n", 0, 0, 0, 1, 1, INT_MAX, 10, 1, 10, INT_MIN);

/* precision and space flag */
printf("p+space: % .3d % .4d % .5d % .6d % .7d % .11d % .12d % .1d % .1d\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);
printf("p+space: % .3i % .4i % .5i % .6i % .7d % .11i % .12i % .1i % .1i\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);

/* precision and + flag */
printf("p+plus: %+.3d %+.4d %+.5d %+.6d %+.7d %+.11d %+.12d %+.1d %+.1d\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);
printf("p+plus: %+.3i %+.4i %+.5i %+.6i %+.7d %+.11i %+.12i %+.1i %+.1i\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);

/* width and precision and alt flag */
printf("w+p+alt: %#5.3x %#1.4x %#2.5x %#10.6x %#11.7x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+p+alt: %#5.3X %#1.4X %#2.5X %#10.6X %#11.7X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+p+alt: %#5.3o %#1.4o %#2.5o %#10.6o %#11.7o\n", 0, 1, 123, INT_MAX, UINT_MAX);

/* width and precision and zero flag */
#ifdef IGNORED
printf("w+p+zero: %01.3d %07.3d %02.3d %011.4d %05.5d %013.11d %04.12d\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX);
printf("w+p+zero: %01.3i %07.3i %02.3i %011.4i %05.5i %013.11i %04.12i\n", 0, 1, 123, -1, -123, INT_MIN, INT_MAX);
printf("w+p+zero: %01.3x %07.4x %02.5x %011.6x %05.7x\n", 0, 1, 123, INT_MAX, UINT_MAX);
#endif /* IGNORED */

/* width and precision and dash flag */
printf("w+p+dash: %-4.3d %-5.3d %-6.4d %-2.5d %-8.6d, %-3.11d %-4.12d\n", 0, 1, 123, -123, INT_MIN, INT_MAX, 1);
printf("w+p+dash: %-4.3i %-5.3i %-6.4i %-2.5i %-8.6i, %-3.11i %-4.12i\n", 0, 1, 123, -123, INT_MIN, INT_MAX, 1);
printf("w+p+dash: %-4.3x %-5.4x %-6.5x %-2.6x %-8.12x\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+p+dash: %-4.3X %-5.4X %-6.5X %-2.6X %-8.12X\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+p+dash: %-4.3o %-5.4o %-6.5o %-2.6o %-8.12o\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+p+dash: %-4.3u %-5.4u %-6.5u %-2.6u %-8.12u\n", 0, 1, 123, INT_MAX, UINT_MAX);
printf("w+p+dash: %-*.*d %-*.*d %-*.*d %-*.*d %-*.*d\n", 0, 0, 0, -1, 0, 1, -1, 1, INT_MAX, -2, 10, 1, -12, 10, INT_MIN);
printf("w+p+dash: %-*.*i %-*.*i %-*.*i %-*.*i %-*.*i\n", 0, 0, 0, -1, 0, 1, -1, 1, INT_MAX, -2, 10, 1, -12, 10, INT_MIN);

/* width and precision and space flag */
printf("w+p+space: % *.3d % 1.3d % 2.4d % 7.5d % 9.6d % 11.7d % 3.11d % 4.12d % 2.1d % 4.1d\n", 0, 0, 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);
printf("w+p+space: % *.3i % 1.3d % 2.4i % 7.5i % 9.6i % 11.7d % 3.11i % 4.12i % 2.1i % 4.1i\n", 0, 0, 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);

/* width and precision and + flag */
printf("w+p+plus: %+*.3d %+1.4d %+2.5d %+8.6d %+11.7d %+3.11d %+15.12d %+16.1d %+2.1d\n", 0, 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);
printf("w+p+plus: %+*.3i %+1.4i %+2.5i %+8.6i %+11.7d %+3.11i %+15.12i %+16.1i %+2.1i\n", 0, 0, 1, 123, -1, -123, INT_MIN, INT_MAX, INT_MIN, INT_MAX);

/* negative width and precision */
printf("w<0+p: %*.0d %*.5d %*.7d %*.1d\n", -1, 0, -10, 2, -1, INT_MIN, -10, INT_MAX);

/* width and negative precision */
printf("w+p<0: %3.*d %4.*d %12.*i %2.*i\n", -1, 5, -12, -1, -1, INT_MIN, -10, INT_MAX);

/* width and alt and zero */
printf("w+alt+zero: %#01x %#02x %#05x %#02x %#07x %#011x %#011x\n", 0, 1, 123, INT_MAX, 123, INT_MAX, UINT_MAX);
printf("w+alt+zero: %#01X %#02X %#05X %#02X %#07X %#011X %#011X\n", 0, 1, 123, INT_MAX, 123, INT_MAX, UINT_MAX);
printf("w+alt+zero: %#01o %#02o %#05o %#02o %#07o %#011o %#011o\n", 0, 1, 123, INT_MAX, 123, INT_MAX, UINT_MAX);

/* width and alt and dash */
printf("w+alt+zero: %#-1x %#-2x %#-5x %#-2x %#-7x %#-11x %#-11x\n", 0, 1, 123, INT_MAX, 123, INT_MAX, UINT_MAX);
printf("w+alt+zero: %#-1X %#-2X %#-5X %#-2X %#-7X %#-11X %#-11X\n", 0, 1, 123, INT_MAX, 123, INT_MAX, UINT_MAX);
printf("w+alt+zero: %#-1o %#-2o %#-5o %#-2o %#-7o %#-11o %#-11o\n", 0, 1, 123, INT_MAX, 123, INT_MAX, UINT_MAX);

/* width and zero and space */
printf("w+zero+space: %0 *d %0 1d %0 5d %0 7d %0 11d %0 5d %0 12d %0 13d\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);
printf("w+zero+space: %0 *i %0 1i %0 5i %0 7i %0 11i %0 5i %0 12i %0 13i\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);

/* width and zero and plus */
printf("w+zero+space: %0+*d %0+1d %0+5d %0+7d %0+11d %0+5d %0+12d %0+13d\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);
printf("w+zero+space: %0+*i %0+1i %0+5i %0+7i %0+11i %0+5i %0+12i %0+13i\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);

/* width and zero and space and plus */
#ifdef IGNORED
printf("w +zero +space: %0 +*d %0 +1d %0 +5d %0 +7d %0 +11d %0 +5d %0 +12d %0 +13d\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);
printf("w +zero +space: %0 +*i %0 +1i %0 +5i %0 +7i %0 +11i %0 +5i %0 +12i %0 +13i\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);
#endif /* IGNORED */

/* width and dash and plus */
printf("w+zero+space: %-+*d %-+1d %-+5d %-+7d %-+11d %-+5d %-+12d %-+13d\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);
printf("w+zero+space: %-+*i %-+1i %-+5i %-+7i %-+11i %-+5i %-+12i %-+13i\n", 0, 0, 1, 123, INT_MAX, INT_MIN, INT_MAX, INT_MIN, -1);

/* TODO */
