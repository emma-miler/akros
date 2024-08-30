#include "efi.h"
#include "io/ConsoleDevice.h"
#include "log.h"
#include "log/BasicLogger.h"

extern "C" int __cdecl _purecall();

int _purecall()
{
    log_panic(g_EfiSystemTable, u"pure virtual call");
    return 0;
}

void SetupGlobals(EFI_SYSTEM_TABLE* table) { g_EfiSystemTable = table; }

void event_notify(EFI_EVENT Event, VOID* Context)
{
    info(g_EfiSystemTable, u"event triggered");
}

typedef struct {
  UINTN Signature;
  EFI_EVENT PeriodicTimer;
  EFI_EVENT OneShotTimer;
  //
  // Other device specific fields
  //
} EXAMPLE_DEVICE;

EFI_STATUS efi_main(EFI_HANDLE handle, EFI_SYSTEM_TABLE* system)
{
    info(system, u"Initializing bootstrap globals\r\n");
    SetupGlobals(system);

    ConsoleDevice dev = ConsoleDevice{};
    BasicLogger logger = BasicLogger(dev);
    logger.Info(u"logger test: %d\n", 25);
    logger.Info(u"size of char %d\n", sizeof(u'a'));

    EFI_TIME time;
    EFI_TIME_CAPABILITIES caps;
    while(1)
    {
        system->BootServices->Stall(1000000);
        system->RuntimeServices->GetTime(&time, &caps);
        logger.Info(u"Time: %d-%d-%d %d:%d:%d\n", time.Year, time.Month, time.Day, time.Hour, time.Minute, time.Second);
    }

    log_panic(system, u"Kernel initialized, waiting in hot loop");

    return EFI_SUCCESS;
}