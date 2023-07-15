#include "primitives.h"

pointd_t graphics_create_pointd(double x, double y)
{
    pointd_t point;
    point.type = PRIMITIVE_POINTD;
    point.x = x;
    point.y = y;
    return point;
}

rect_t graphics_create_rect(double x, double y, double width, double height)
{
    rect_t rect;
    rect.type = PRIMITIVE_RECT;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    return rect;
}

line_t graphics_create_line(double x1, double y1, double x2, double y2)
{
    line_t line;
    line.type = PRIMITIVE_LINE;
    line.x1 = x1;
    line.y1 = y1;
    line.x2 = x2;
    line.y2 = y2;
    return line;
}

tri_t graphics_create_tri(pointd_t* p1, pointd_t* p2, pointd_t* p3)
{
    tri_t tri;
    tri.type = PRIMITIVE_TRI;
    tri.p1 = *p1;
    tri.p2 = *p2;
    tri.p3 = *p3;
    return tri;
}
