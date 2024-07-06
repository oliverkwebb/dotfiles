.POSIX:
.PHONY: all clean

Q = @
CC=gcc
DEST=bin
STDFLAGS=-std=c99 -D_GNU_SOURCE
OPTFLAGS=-O2 -flto -fconserve-stack
WARNFLAGS=-Wall -Wextra -Wpedantic
CFLAGS=$(STDFLAGS) $(OPTFLAGS) $(WARNFLAGS)

CFILES := $(wildcard *.c)
BINS   := $(CFILES:%.c=%)

all: ${BINS}
	
clean:
	rm -f $(DEST)/*

%: %.c
	@printf "CC %7s -> $(DEST)/$@\n" $<
	$(Q)$(CC) $(CFLAGS) $< -o "$(DEST)/$@"

