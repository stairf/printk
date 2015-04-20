# *** MAKEFILE ***

#
# Copyright (c) 2015, Stefan Reif
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

PROG     := test
CC       := gcc
CFLAGS   := -std=c99 -D_XOPEN_SOURCE=700 -g -O3 -Wall -Wextra -Wno-format
LD       := gcc
LDFLAGS  := $(CFLAGS)
CFLAGS   += -fstack-protector-all -fstack-check



C_SRC := $(wildcard *.c)
C_OBJ := $(C_SRC:%.c=%.o)
HDR   := $(wildcard *.h)

.PHONY: all clean
all: $(PROG)

clean:
	$(RM) $(PROG) $(C_OBJ)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c -o $@ $<


$(PROG): $(C_OBJ) $(T_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^


