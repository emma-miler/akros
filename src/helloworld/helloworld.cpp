#include "../efi.h"

EFI_STATUS efi_main(EFI_HANDLE handle, EFI_SYSTEM_TABLE* system)
{
    int* test = (int*)900420;
    *test = 42;
    return 0;
    
}