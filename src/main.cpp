#include "efi.h"
#include "io/ConsoleDevice.h"
#include "log.h"
#include "log/BasicLogger.h"

extern "C" int __cdecl _purecall();

int _purecall()
{
    log_panic(g_EfiSystemTable, "pure virtual call");
    return 0;
}

void SetupGlobals(EFI_SYSTEM_TABLE* table) { g_EfiSystemTable = table; }

EFI_STATUS efi_main(EFI_HANDLE handle, EFI_SYSTEM_TABLE* system)
{
    info(system, "Initializing bootstrap globals\r\n");
    SetupGlobals(system);

    ConsoleDevice dev = ConsoleDevice{};
    BasicLogger logger = BasicLogger(dev);
    logger.Info("logger test: %d\n", 25);

    info(system, "Setting up the loader...\r\n");
    log_panic(system, "C++ loader working with new EFI");

    return EFI_SUCCESS;
}