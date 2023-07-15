#pragma once

#include "../uefi/uefi.h"
#include "../libs/ssfn.h"

typedef enum
{
    PRIMITIVE_TEXT = 0,
    PRIMITIVE_POINT = 1,
    PRIMITIVE_LINE = 2,
    PRIMITIVE_TRI= 3,
    PRIMITIVE_RECT = 4,
} primitive_type_t;

typedef struct
{
    double x;
    double y;
    char* text;
} label_t;
label_t new_label_t(double x, double y, char* text);


typedef struct
{
    double x;
    double y;
} point_t;
point_t new_point_t(double x, double y);

typedef struct
{
    double x1;
    double y1;
    double x2;
    double y2;
} line_t;

typedef struct
{
    point_t p1;
    point_t p2;
    point_t p3;
} tri_t;

typedef struct
{
    double x;
    double y;
    double width;
    double height;
    char isFilled;
} rect_t;
rect_t new_rect_t(double x, double y, double width, double height);


typedef union
{
    label_t as_label;
    point_t as_point;
    line_t as_line;
    rect_t as_rect;
    tri_t as_tri;
} primitive_t;
