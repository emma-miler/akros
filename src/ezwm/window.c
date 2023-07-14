#include "window.h"
#include "../macros.h"

ezwm_window_t* ezwm_window_Create(rect_t rect, char* title)
{
    ezwm_window_t* window = malloc(sizeof(ezwm_window_t));
    size_t title_length = strlen(title);
    window->title = malloc(sizeof(char) * title_length);
    strcpy(window->title, title);

    window->rect = rect;

    return window;
}

ezwm_window_singleton_t* ezwm_window_singleton_init()
{
    ezwm_window_singleton_t* window = malloc(sizeof(ezwm_window_singleton_t));
    IMPL(ezwm, window, Create)
    return window;
}
