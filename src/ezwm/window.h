#pragma once

#include "../graphics/buffer.h"
#include "../graphics/primitives.h"

struct ezwm_window_t;
typedef struct {
    char* title;
    rect_t rect;
} ezwm_window_t;

typedef struct
{
    ezwm_window_t* (*Create)(rect_t rect, char* title);
} ezwm_window_singleton_t;

ezwm_window_singleton_t* ezwm_window_singleton_init();
