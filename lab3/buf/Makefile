# CSCI 1310 Lab 3 Makefile

# Standard C compiler
PROCESSOR_ARCHITECTURE := $(shell arch)
ifeq ($(PROCESSOR_ARCHITECTURE),arm64)
	CC := x86_64-linux-gnu-gcc-9
else ifeq ($(PROCESSOR_ARCHITECTURE),aarch64)
	CC := x86_64-linux-gnu-gcc-9
else
	CC := gcc
endif

# Regular compilation flags
CFLAGS := -O0 -g -std=c99 -Wall -Werror -Wno-deprecated-declarations # Flags for C compilation

# Compilation flags that ensure that the stack is static and with no security measures
STACKFLAGS := -Wno-implicit -fno-stack-protector -no-pie -fno-pic -z execstack -z norelro -fcf-protection=none

# rules that are listed as .PHONY do not produce an output file
.PHONY: all do_hack clean

all: buffer exploit

# Compile the hackable buffer program
buffer: buffer.c
	$(CC) $(CFLAGS) $(STACKFLAGS) -o $@ $^
ifeq ($(PROCESSOR_ARCHITECTURE),arm64)
	@ x86_64-linux-gnu-objdump -d $@ > buffer_asm.txt
else ifeq ($(PROCESSOR_ARCHITECTURE),aarch64)
	@ x86_64-linux-gnu-objdump -d $@ > buffer_asm.txt
else
	@ objdump -d $@ > buffer_asm.txt
endif

# Compile the exploit printing program
exploit: exploit.c
	$(CC) $(CFLAGS) -o $@ $^

#dump contents of exploit to file
exploit_text1: exploit
	@ ./exploit > exploit1.txt

exploit_text2: exploit
	@ ./exploit > exploit2.txt

#pipe output of exploit printing program into buffer program
do_hack: buffer
	@ echo "Testing Buffer ... "
	./exploit | ./buffer


clean:
	@ rm -rf buffer exploit exploit1.txt  exploit2.txt buffer_asm.txt
