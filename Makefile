CC := clang++
LD := lld
ARCH ?= x86-64

SHELL := bash -O globstar

ifeq ($(ARCH),x86-64)
include x86-64.env
else
include aarch64.env
endif

export

SRCS := main.cpp clib.cpp log.cpp efi.cpp log/BasicLogger.cpp io/EFIOutputDevice.cpp io/EFIInputDevice.cpp io/ConsoleDevice.cpp app/shell/shell.cpp
OBJS := $(patsubst %.cpp,build/src/%.o,$(SRCS))

SRCS_HELLO := helloworld/helloworld.cpp
OBJS_HELLO := $(patsubst %.cpp,build/src/%.o,$(SRCS_HELLO))

default: all

make_dirs:
	echo CREATING DIRECTORIES
	mkdir -p build/src
	mkdir -p build/src/io
	mkdir -p build/src/log
	mkdir -p build/src/app/shell
	mkdir -p build/src/helloworld
	mkdir -p build/EFI/BOOT

build/%.o: %.cpp
	echo BUILDING CPP
	$(CC) $(CFLAGS) -c $^ -o $@

boot.efi: $(OBJS)
	echo LINKING BOOT.EFI
	$(LD) $(LDFLAGS) $^ -out:build/EFI/BOOT/BOOTX64.EFI

helloworld: $(OBJS_HELLO)
	echo LINKING HELLOWORLD
	$(CC) $(CFLAGS) -c src/helloworld/helloworld.cpp -o build/src/helloworld/helloworld.o
	$(LD) $(LDFLAGS) build/src/helloworld/helloworld.o -out:build/helloworld.exe

-include $(SRCS:.c=.d)

.PHONY: clean all default

all: make_dirs boot.efi helloworld

clean:
	rm -rf build/EFI/BOOT/*.efi build/**/*.o build/**/*.d build/**/*.lib
