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

SRCS := main.cpp clib.cpp log.cpp efi.cpp io/ConsoleDevice.cpp log/BasicLogger.cpp
OBJS := $(patsubst %.cpp,build/src/%.o,$(SRCS))

default: all

make_dirs:
	echo CREATING DIRECTORIES
	mkdir -p build/src
	mkdir -p build/src/io
	mkdir -p build/src/log
	mkdir -p build/EFI/BOOT

build/%.o: %.cpp
	echo BUILDING CPP
	$(CC) $(CFLAGS) -c $^ -o $@

boot.efi: $(OBJS)
	echo BUILDING BOOT.EFI
	$(LD) $(LDFLAGS) $^ -out:build/EFI/BOOT/BOOTX64.EFI

-include $(SRCS:.c=.d)

.PHONY: clean all default

all: make_dirs boot.efi

clean:
	rm -rf build/EFI/BOOT/*.efi build/**/*.o build/**/*.d build/**/*.lib
