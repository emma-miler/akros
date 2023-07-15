#include "uefi/uefi.h"

#define SSFN_IMPLEMENTATION     /* get the normal renderer implementation */
#define SSFN_CONSOLEBITMAP_HICOLOR
#define SSFN_MAXLINES 4096      /* configure for static memory management */

#include "graphics/graphics.h"
#include "graphics/buffer.h"
#include "graphics/font.h"
#include "graphics/primitives.h"
#include "ezwm/ezwm.h"
#include "display/ads.h"

ssfn_buf_t dst = {0};           /* framebuffer properties */
ssfn_t ctx = {0};

ezwm_window_t* windows[4];
uint32_t colors[4] = {0xFFFF0000, 0xFFFF00FF, 0xFFFFFF00, 0xFFFFFFFF};

int main (int argc, char **argv)
{


  int x = 0, y = 0;
  efi_gop_t* gop = akr_graphics_GetGop();
  if (gop == NULL) { printf("Error getting GOP"); exit(1); };
  akr_graphics_SetMode(gop);

  scrbuf_t* buf = scrbuf_Create(gop, &ctx, &dst, gop->Mode->Information->HorizontalResolution, gop->Mode->Information->VerticalResolution);
  scrbuf_t* temp_buf = scrbuf_Create(gop, &ctx, &dst, gop->Mode->Information->HorizontalResolution, gop->Mode->Information->VerticalResolution);

  ssfn_font_t* font = akr_font_load("font.sfn", &ctx);

  ssfn_select(buf->ssfn_ctx, SSFN_FAMILY_ANY, NULL, SSFN_STYLE_REGULAR | SSFN_STYLE_NOCACHE | SSFN_STYLE_NOAA, 16);

  ads_session_t* session = ads_create_session(buf, temp_buf);

  ezwm_window_t* window = ezwm_window_Create(new_rect_t(50,50,300,300), "test window");


  // Window mask
  rect_t* mask = malloc(sizeof(rect_t));
  mask->x = window->rect.x;
  mask->y = window->rect.y - 20;
  mask->width = window->rect.width;
  mask->height = window->rect.height + 20;

  int t = 0;
  int direction = 1;
  while (1)
  {
    t += direction;
    if (t > 400 || t < 1)
    {
      direction = -direction;
    }

    ezwm_window_draw_decorations(window, session);

    // Background drawcall
    ads_append_drawcall(session, drawcall_from_rect(window->rect, 0xFF303030));

    // Rect drawcall
    rect_t rect;
    rect.x = t + 50;
    rect.y = 50;
    rect.width = 100;
    rect.height = 100;
    drawcall_t call = drawcall_from_rect(rect, 0xFFFF0000);
    ads_append_drawcall(session, call);

    scrbuf_Clear(temp_buf);

    ads_process_drawcalls(session);

    scrbuf_Clear(buf);
    scrbuf_Copy(buf, temp_buf, mask);


    scrbuf_Activate(buf);
  }
  sleep(-1);

  return 0;
}
