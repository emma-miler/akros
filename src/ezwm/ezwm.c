#include "ezwm.h"
#include "window.h"

ezwm_singleton_t* EZWM;

void ezwm_init()
{
    EZWM = malloc(sizeof(ezwm_singleton_t));
    EZWM->Window = ezwm_window_singleton_init();
}
