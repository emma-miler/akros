#pragma once

#include "../graphics/buffer.h"
#include "../graphics/primitives.h"

struct ezwm_window_t;
typedef struct {
    char* title;
    rect_t rect;
} ezwm_window_t;

ezwm_window_t* ezwm_window_Create(rect_t rect, char* title);
