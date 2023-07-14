#pragma once

#include "window.h"

typedef struct
{
    ezwm_window_singleton_t* Window;
} ezwm_singleton_t;
extern ezwm_singleton_t* EZWM;
void ezwm_init();
