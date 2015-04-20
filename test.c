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
 * test.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "printk.h"

static void die(const char msg[])
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void xgetline(char **lptr, size_t *nptr, FILE *stream)
{
	if (0 > getline(lptr, nptr, stream)) {
		if (feof(stream)) {
			free(*lptr);
			*lptr = NULL;
			*nptr = 0;
			return;
		}
		die("getline");
	}
}

#define READ  0
#define WRITE 1

static void do_test_str(size_t bufsz, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char libc[bufsz];
	char test[bufsz];

	vsnprintf(libc, bufsz, fmt, ap);
	vsnprintk(test, bufsz, fmt, ap);

	if (strcmp(libc, test))
		fprintf(stderr, "[str:%zu] error\n\tlibc='%s'\n\ttest='%s'\n", bufsz, libc, test);

	va_end(ap);
}


static void test_str(size_t bufsz)
{
#define printf(...) do_test_str(bufsz, __VA_ARGS__)
#include "tests.h"
#undef printf
}


int main(void)
{
	int pipe_libc[2];
	int pipe_test[2];

	if (pipe(pipe_libc) || pipe(pipe_test))
		die("pipe");

	pid_t libcpid = fork();
	if (libcpid < 0)
		die ("fork");
	if (libcpid == 0) {
		close(pipe_libc[READ]);
		close(pipe_test[READ]);
		close(pipe_test[WRITE]);
		dup2(pipe_libc[WRITE], STDOUT_FILENO);
#include "tests.h"
		exit (EXIT_SUCCESS);
	}

	pid_t testpid = fork();
	if (testpid < 0)
		die("fork");
	if (testpid == 0) {
		close(pipe_libc[READ]);
		close(pipe_libc[WRITE]);
		close(pipe_test[READ]);
		dup2(pipe_test[WRITE], STDOUT_FILENO);
#define printf printk
#include "tests.h"
#undef printf
		exit(EXIT_SUCCESS);
	}

	close(pipe_libc[WRITE]);
	close(pipe_test[WRITE]);
	FILE *libc_in = fdopen(pipe_libc[READ], "r");
	if (!libc_in)
		die("fdopen (libc)");
	FILE *test_in = fdopen(pipe_test[READ], "r");
	if (!test_in)
		die("fdopen (test)");

	unsigned int lineno = 1;
	char *libc_line = NULL;
	char *test_line = NULL;
	size_t libc_linelen = 0;
	size_t test_linelen = 0;
	while (1) {

		xgetline(&libc_line, &libc_linelen, libc_in);
		xgetline(&test_line, &test_linelen, test_in);

		if (!libc_line || !test_line) {
			if (libc_line && !test_line) {
				fprintf(stderr, "%u: test=EOF libc=%s", lineno, libc_line);
				free(libc_line);
				free(test_line);
				exit(EXIT_FAILURE);
			} else if(!libc_line && test_line) {
				fprintf(stderr, "%u: libc=EOF test=%s", lineno, test_line);
				free(libc_line);
				free(test_line);
				exit(EXIT_FAILURE);
			}
			break;
		}

		if (strcmp(libc_line, test_line))
			fprintf(stderr, "%u: error\n\tlibc='%s'\n\ttest='%s'\n", lineno, libc_line, test_line);
		lineno++;

	}
	fclose(libc_in);
	fclose(test_in);

	test_str(1024);
	test_str(4);
	test_str(1);
	test_str(0);

	return 0;

}
