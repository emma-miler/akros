#pragma once

#include "../graphics/buffer.h"
#include "../graphics/primitives.h"
#include "../graphics/session.h"

struct ezwm_window_t;
typedef struct {
    char* title;
    rect_t rect;
} ezwm_window_t;

ezwm_window_t* ezwm_window_Create(rect_t rect, char* title);
void ezwm_window_draw_decorations(ezwm_window_t* window, ads_session_t* session);
