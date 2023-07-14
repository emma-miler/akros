#include "uefi/uefi.h"

#define SSFN_IMPLEMENTATION     /* get the normal renderer implementation */
#define SSFN_CONSOLEBITMAP_HICOLOR
#define SSFN_MAXLINES 4096      /* configure for static memory management */

#include "graphics/graphics.h"
#include "graphics/buffer.h"
#include "graphics/font.h"
#include "ezwm/ezwm.h"

ssfn_buf_t dst = {0};           /* framebuffer properties */
ssfn_t ctx = {0};

ezwm_window_t* windows[4];
uint32_t colors[4] = {0xFFFF0000, 0xFFFF00FF, 0xFFFFFF00, 0xFFFFFFFF};

int main (int argc, char **argv)
{
  akr_init_graphics();
  ezwm_init();
  int x = 0, y = 0;
  efi_gop_t* gop = Graphics->GetGop();
  if (gop == NULL) { printf("Error getting GOP"); exit(1); };
  Graphics->SetMode(gop);

  akr_scrbuf_t* buf = Graphics->Screen->Create(gop, &ctx, &dst, gop->Mode->Information->HorizontalResolution, gop->Mode->Information->VerticalResolution);

  ssfn_font_t* font = akr_font_load("font.sfn", &ctx);

  ssfn_select(buf->ssfn_ctx, SSFN_FAMILY_ANY, NULL, SSFN_STYLE_REGULAR | SSFN_STYLE_NOCACHE | SSFN_STYLE_NOAA, 16);

  for (int i = 0; i < 4; i++)
  {
    rect_t rect;
    rect.width = 100;
    rect.height = 100;
    rect.x = 120 * i + 20;
    rect.y = 50 * i + 50;
    char* title = "test x";
    title[5] = i + 65;
    ezwm_window_t* window = EZWM->Window->Create(rect, title);
    windows[i] = window;

  }


  for (int i = 0; i < 4; i++)
  {
    rect_t* rect = &windows[i]->rect;
    Graphics->Screen->DrawRect(buf, rect->x - 1, rect->y - 12, rect->x + rect->width, rect->y + 8, 0xFF444444);
    Graphics->Screen->DrawText(buf, rect->x + 2, rect->y, windows[i]->title);
    Graphics->Screen->DrawRect(buf, rect->x, rect->y + 4, rect->x + rect->width, rect->y + rect->height, colors[i]);
  }

  //Graphics->Screen->DrawRect(smallbuf, 0, 0, smallbuf->width, smallbuf->height, 0xFFFF0000);
  //Graphics->Screen->Overlay(buf, smallbuf, 100, 100);
  Graphics->Screen->Activate(buf);

  //akr_scrbuf_activate(textbuffer);
  sleep(-1);

  return 0;
}
