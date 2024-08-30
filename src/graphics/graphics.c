#include "../uefi/uefi.h"

#include "../macros.h"

#include "graphics.h"


efi_gop_t* akr_graphics_GetGop()
{
    efi_status_t status;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    status = BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    if(EFI_ERROR(status) || !gop) {
        printf("unable to get graphics output protocol\n");
        return NULL;
    }
    return gop;
}


int akr_graphics_SetMode(efi_gop_t* gop)
{
    efi_status_t status;
    status = gop->SetMode(gop, 9);
    if(EFI_ERROR(status)) {
        printf("unable to set video mode\n");
        return 0;
    }
    ST->ConOut->Reset(ST->ConOut, 0);
    ST->StdErr->Reset(ST->StdErr, 0);

    return 1;
}
