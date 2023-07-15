#pragma once

#include "../uefi/uefi.h"

typedef struct
{
    char type;
} primitive_base_t;

typedef enum
{
    PRIMITIVE_POINTD = 1,
    PRIMITIVE_RECT = 2,
    PRIMITIVE_LINE= 3,
    PRIMITIVE_TRI = 4,
} primitive_type_t;

typedef struct
{
    char type;
    double x;
    double y;
} pointd_t;
pointd_t graphics_create_pointd(double x, double y);


typedef struct
{
    char type;
    double width;
    double height;
    double x;
    double y;
} rect_t;
rect_t graphics_create_rect(double x, double y, double width, double height);

typedef struct
{
    char type;
    double x1;
    double y1;
    double x2;
    double y2;
} line_t;
line_t graphics_create_line(double x1, double y1, double x2, double y2);

// WARNING: this is a variable-sized struct
typedef struct
{
    char type;
    pointd_t p1;
    pointd_t p2;
    pointd_t p3;
} tri_t;
tri_t graphics_create_tri(pointd_t* p1, pointd_t* p2, pointd_t* p3);


typedef union
{
    primitive_base_t base;
    pointd_t as_point;
    line_t as_line;
    rect_t as_rect;
    tri_t as_tri;
} primitive_t;
