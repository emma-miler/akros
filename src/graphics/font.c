#include "../uefi/uefi.h"
#include "font.h"
#include "buffer.h"

ssfn_font_t* akr_font_load(char* filename, ssfn_t* ctx)
{
    FILE* f;
    long size;
    ssfn_font_t* font;

    f = fopen(filename, "r");
    if (!f)
    {
        printf("Unable to load font\n");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    font = (ssfn_font_t*)malloc(size + 1);
    if(!font) {
        printf("unable to allocate memory\n");
        return NULL;
    }
    fread(font, size, 1, f);
    fclose(f);
    ssfn_load(ctx, font);
    return font;
}
