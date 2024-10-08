#include "clib.h"

#include <stdbool.h>

enum format_type_width {
    FMT_TYPE_CHAR,
    FMT_TYPE_SHORT,
    FMT_TYPE_INT,
    FMT_TYPE_LONG,
    FMT_TYPE_LONG_LONG,
    FMT_TYPE_SIZE,
    FMT_TYPE_PTRDIFF,
    FMT_TYPE_NONE,
};

enum format_type {
    FMT_SCHAR,
    FMT_SHORT_INT,
    FMT_INT,
    FMT_LONG_INT,
    FMT_LONG_LONG_INT,
    FMT_char,
    FMT_SHORT_UINT,
    FMT_UINT,
    FMT_LONG_UINT,
    FMT_LONG_LONG_UINT,
    FMT_SIZE,
    FMT_PTR,
    FMT_PTRDIFF,
    FMT_STR,
    FMT_UEFI_STR,
    FMT_PERCENT,
    FMT_CHAR,
    FMT_NONE,
};

const unsigned FMT_FLAG_MINUS = 1;
const unsigned FMT_FLAG_PLUS = 2;
const unsigned FMT_FLAG_SPACE = 4;
const unsigned FMT_FLAG_BASE = 8;
const unsigned FMT_FLAG_ZERO = 16;

struct format {
    unsigned flags;
    bool width_from_args;
    unsigned width;
    enum format_type_width type_width;
    enum format_type type;
    unsigned base;
    size_t size;
};

template <typename T> class Buffer {
  public:
    T* storage;
    size_t size;
    size_t count;

    Buffer(T* storage, size_t size, size_t count) : storage(storage), size(size), count(count) {}

    void append(int code)
    {
        if (count < size)
            storage[count] = code;
        ++count;
    }

    void copy(const uchar* begin, const uchar* end)
    {
        const size_t len = end - begin;
        const size_t rem = count < size ? size - count : 0;
        const size_t copy = len < rem ? len : rem;
        T* pos = storage + count;

        for (size_t i = 0; i < copy; ++i)
            *pos++ = begin[i];
        count += len;
    }

    void format_unsigned(struct format* config, unsigned long long v)
    {
        uchar buf[32];
        uchar* pos = buf;

        do {
            const unsigned d = v % config->base;

            v = v / config->base;
            if (d < 10)
                *pos = d + '0';
            else
                *pos = d - 10 + 'A';
            ++pos;
        } while (v);

        for (uchar *l = buf, *r = pos - 1; l < r; ++l, --r) {
            const uchar c = *l;

            *l = *r;
            *r = c;
        }

        copy(buf, pos);
    }

    void format_signed(struct format* config, long long v)
    {
        if (v < 0) {
            append('-');
            v = -v;
        }
        format_unsigned(config, v);
    }
};

static const uchar* format_parse_flags(const uchar* str, struct format* config)
{
    while (*str) {
        bool is_flag = true;

        switch (*str) {
        case '-':
            config->flags = FMT_FLAG_MINUS;
            break;
        case '+':
            config->flags = FMT_FLAG_PLUS;
            break;
        case ' ':
            config->flags = FMT_FLAG_SPACE;
            break;
        case '#':
            config->flags = FMT_FLAG_BASE;
            break;
        case '0':
            config->flags = FMT_FLAG_ZERO;
            break;
        default:
            is_flag = false;
            break;
        }

        if (!is_flag)
            break;
        ++str;
    }
    return str;
}

static const uchar* format_parse_width(const uchar* str, struct format* config)
{
    if (*str == '*') {
        config->width_from_args = true;
        return str + 1;
    }

    while (isdigit(*str)) {
        config->width = config->width * 10 + (*str - '0');
        ++str;
    }

    return str;
}

static const uchar* format_parse_type_width(const uchar* str, struct format* config)
{
    if (*str == 'z') {
        config->type_width = FMT_TYPE_SIZE;
        return str + 1;
    }

    if (*str == 't') {
        config->type_width = FMT_TYPE_PTRDIFF;
        return str + 1;
    }

    if (*str == 'h') {
        ++str;
        if (*str == 'h') {
            config->type_width = FMT_TYPE_CHAR;
            return str + 1;
        }
        config->type_width = FMT_TYPE_SHORT;
        return str;
    }

    if (*str == 'l') {
        ++str;
        if (*str == 'l') {
            config->type_width = FMT_TYPE_LONG_LONG;
            return str + 1;
        }
        config->type_width = FMT_TYPE_LONG;
        return str;
    }

    return str;
}

static enum format_type format_adjusted_type(enum format_type type, enum format_type_width width)
{
    if (type == FMT_INT) {
        switch (width) {
        case FMT_TYPE_CHAR:
            return FMT_SCHAR;
        case FMT_TYPE_SHORT:
            return FMT_SHORT_INT;
        case FMT_TYPE_LONG:
            return FMT_LONG_INT;
        case FMT_TYPE_LONG_LONG:
            return FMT_LONG_LONG_INT;
        case FMT_TYPE_SIZE:
            return FMT_SIZE;
        case FMT_TYPE_PTRDIFF:
            return FMT_PTRDIFF;
        default:
            return type;
        }
    }

    if (type == FMT_UINT) {
        switch (width) {
        case FMT_TYPE_CHAR:
            return FMT_char;
        case FMT_TYPE_SHORT:
            return FMT_SHORT_UINT;
        case FMT_TYPE_LONG:
            return FMT_LONG_UINT;
        case FMT_TYPE_LONG_LONG:
            return FMT_LONG_LONG_UINT;
        case FMT_TYPE_SIZE:
            return FMT_SIZE;
        case FMT_TYPE_PTRDIFF:
            return FMT_PTRDIFF;
        default:
            return type;
        }
    }

    return type;
}

static const uchar* format_parse_spec(const uchar* str, struct format* config)
{
    const uchar* pos = str;

    if (*pos == '%') {
        config->type = FMT_PERCENT;
        return pos + 1;
    }

    pos = format_parse_type_width(pos, config);

    switch (*pos) {
    case 'd':
    case 'i':
    case 'u':
        config->base = 10;
        break;
    case 'o':
        config->base = 8;
        break;
    case 'x':
    case 'X':
    case 'p':
        config->base = 16;
        break;
    }

    switch (*pos) {
    case 'd':
    case 'i':
        config->type = format_adjusted_type(FMT_INT, config->type_width);
        break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
        config->type = format_adjusted_type(FMT_UINT, config->type_width);
        break;
    case 'c':
        config->type = FMT_CHAR;
        break;
    case 's':
        config->type = FMT_STR;
        break;
    case 'w':
        config->type = FMT_UEFI_STR;
        break;
    case 'p':
        config->type = FMT_PTR;
        break;
    default:
        return str;
    }

    return pos + 1;
}

static int format_parse(const uchar* str, struct format* config)
{
    const uchar* pos = str;
    const uchar* end;

    config->flags = 0;
    config->width_from_args = false;
    config->width = 0;
    config->type_width = FMT_TYPE_NONE;
    config->type = FMT_NONE;
    config->base = 0;
    config->size = 0;

    pos = format_parse_flags(pos, config);
    pos = format_parse_width(pos, config);

    // The spec is the only mandatory part, so if it's empty it's a problem
    end = format_parse_spec(pos, config);
    if (pos == end)
        return -1;
    config->size = end - str;

    return 0;
}
#include "log.h"

int snprintf(uchar* writebuffer, size_t size, const uchar* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = vsnprintf(writebuffer, size, fmt, args);
    va_end(args);
    return ret;
}

int vsnprintf(uchar* writebuffer, size_t size, const uchar* fmt, va_list args)
{
    Buffer<uchar> buf = Buffer<uchar>(writebuffer, size - 1, 0);
    const uchar* current = fmt;

    while (*current) {
        const uchar* start = current;
        const uchar* end = current;

        struct format config;
        unsigned long long uv;
        long long v;
        int ret;

        while (*end && *end != '%')
            ++end;

        buf.copy(start, end);
        if (*end == '\0') {
            current = end;
            break;
        }

        ret = format_parse(end + 1, &config);
        if (ret < 0)
            return ret;
        current = end + 1 + config.size;

        if (config.width_from_args)
            config.width = (unsigned)va_arg(args, int);

        switch (config.type) {
        case FMT_STR: {
            const uchar* str = va_arg(args, const uchar*);
            buf.copy(str, str + strlen(str));
            break;
        }
        case FMT_UEFI_STR: {
            log_panic(g_EfiSystemTable, u"FMT_UEFI_STR not supported lmao\n");
        }
        case FMT_CHAR: {
            int v = va_arg(args, int);
            buf.append(v);
            break;
        }
        case FMT_PERCENT:
            buf.append('%');
            break;
        case FMT_SCHAR:
        case FMT_SHORT_INT:
        case FMT_INT:
            v = va_arg(args, int);
            buf.format_signed(&config, v);
            break;
        case FMT_LONG_INT:
            v = va_arg(args, long);
            buf.format_signed(&config, v);
            break;
        case FMT_LONG_LONG_INT:
            v = va_arg(args, long long);
            buf.format_signed(&config, v);
            break;
        case FMT_PTRDIFF:
            v = (long long)va_arg(args, ptrdiff_t);
            buf.format_unsigned(&config, v);
            break;
        case FMT_char:
        case FMT_SHORT_UINT:
        case FMT_UINT:
            uv = va_arg(args, unsigned);
            buf.format_unsigned(&config, uv);
            break;
        case FMT_LONG_UINT:
            uv = va_arg(args, unsigned long);
            buf.format_unsigned(&config, uv);
            break;
        case FMT_LONG_LONG_UINT:
            uv = va_arg(args, unsigned long long);
            buf.format_unsigned(&config, uv);
            break;
        case FMT_SIZE:
            uv = va_arg(args, size_t);
            buf.format_unsigned(&config, uv);
            break;
        case FMT_PTR:
            uv = (unsigned long long)va_arg(args, void*);
            buf.format_unsigned(&config, uv);
            break;
        default:
            return -1;
        }
    }

    if (buf.count < buf.size)
        buf.storage[buf.count] = '\0';
    else
        buf.storage[buf.size] = '\0';

    return (int)buf.count;
}

size_t strlen(const uchar* str)
{
    const uchar* pos = str;

    while (*pos++)
        ;
    return pos - str - 1;
}

size_t u16strlen(const uint16_t* str)
{
    const uint16_t* pos = str;

    while (*pos++)
        ;
    return pos - str - 1;
}

int strcmp(const char* l, const char* r)
{
    while (*l == *r && *l != '\0') {
        ++l;
        ++r;
    }

    if (*l == *r)
        return 0;

    if (*l < *r)
        return -1;
    else
        return 1;
}

char* strncpy(char* dst, const char* src, size_t size)
{
    size_t i = 0;

    for (; i < size && src[i]; ++i)
        dst[i] = src[i];

    for (; i < size; ++i)
        dst[i] = '\0';

    return dst;
}

uint16_t* to_u16strncpy(uint16_t* dst, const char* src, size_t size)
{
    size_t i = 0;

    for (; i < size && src[i]; ++i)
        dst[i] = src[i];

    for (; i < size; ++i)
        dst[i] = '\0';

    return dst;
}

void* memset(void* ptr, int value, size_t size)
{
    char* to = (char*)ptr;

    for (size_t i = 0; i < size; ++i)
        *to++ = value;
    return ptr;
}

void* memcpy(void* dst, const void* src, size_t size)
{
    const char* from = (char*)src;
    char* to = (char*)dst;

    for (size_t i = 0; i < size; ++i)
        *to++ = *from++;
    return dst;
}

int isdigit(int code) { return code >= '0' && code <= '9'; }

int isalpha(int code) { return (code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z'); }

int isalnum(int code) { return isdigit(code) || isalpha(code); }

int isspace(int code) { return code == ' ' || code == '\r' || code == '\n' || code == '\t'; }
