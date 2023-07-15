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

void ezwm_window_draw_decorations(ezwm_window_t* window, ads_session_t* session)
{
    ads_append_drawcall(session, drawcall_from_rect(new_rect_t(window->rect.x, window->rect.y - 20, window->rect.width, 20), 0xFF303060));
    ads_append_drawcall(session, drawcall_from_label(new_label_t(window->rect.x + 2, window->rect.y - 5, window->title), 0xFFFFFFFF));
}
