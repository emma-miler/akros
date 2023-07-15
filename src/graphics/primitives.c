#include "primitives.h"

label_t new_label_t(double x, double y, char* text)
{
    label_t label = {
        .x=x,
        .y=y,
        .text=text
    };
    return label;
}

point_t new_point_t(double x, double y)
{
    point_t point = {
        .x=x,
        .y=y
    };
    return point;
}

rect_t new_rect_t(double x, double y, double width, double height)
{
    rect_t rect = {
        .x=x,
        .y=y,
        .width=width,
        .height=height,
        .isFilled=1
    };
    return rect;
}
