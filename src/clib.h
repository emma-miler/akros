#ifndef __CLIB_H__
#define __CLIB_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "types.h"

size_t strlen(const uchar* str);
int strcmp(const uchar* l, const uchar* r);

uchar* strncpy(uchar* dst, const uchar* src, size_t size);
void* memcpy(void* dst, const void* src, size_t size);
void* memset(void* ptr, int value, size_t size);

int isdigit(int code);
int isalpha(int code);
int isalnum(int code);
int isspace(int code);

int vsnprintf(uchar* writebuffer, size_t size, const uchar* fmt, va_list args);
size_t u16strlen(const uint16_t* str);
uint16_t* to_u16strncpy(uint16_t* dst, const char* src, size_t size);

#endif // __CLIB_H__
