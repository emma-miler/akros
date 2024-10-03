#include "app/shell/shell.h"
#include "clib.h"
#include "efi.h"
#include "io/ConsoleDevice.h"
#include "io/EFIInputDevice.h"
#include "io/EFIOutputDevice.h"
#include "log.h"
#include "log/BasicLogger.h"
#include "efi/file.h"
#include "efi/image.h"

extern "C" int __cdecl _purecall();

int _purecall()
{
    log_panic(g_EfiSystemTable, u"pure virtual call");
    return 0;
}

void SetupGlobals(EFI_SYSTEM_TABLE* table) { g_EfiSystemTable = table; }

void event_notify(EFI_EVENT Event, VOID* Context) { info(g_EfiSystemTable, u"event triggered"); }

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

    EFIInputDevice inputDev = EFIInputDevice();
    EFIOutputDevice outputDev = EFIOutputDevice();

    EFIOutputDevice output = EFIOutputDevice();
    BasicLogger logger = BasicLogger(output);
    
    // Get files in fs
    EFI_GUID guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_STATUS          			Status;
	EFI_FILE_PROTOCOL    			*RootFS;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFileSystem;
	UINTN	BufSize;
	EFI_FILE_PROTOCOL *FileHandle=0;
    EFI_STATUS status = g_EfiSystemTable->BootServices->LocateProtocol(&guid, NULL,(VOID **)&SimpleFileSystem);
    logger.Info(u"%d\n", status);

    status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &RootFS);
    logger.Info(u"%d\n", status);

    status =RootFS->Open(RootFS, &FileHandle, u"testnew", EFI_FILE_MODE_READ, 0);
    logger.Info(u"%d\n", status);

    uchar buf[255];
    UINTN bufSize = 255;
    FileHandle->Read(FileHandle, &bufSize, &buf);
    logger.Info(buf);


    ConsoleDevice console = ConsoleDevice(outputDev, inputDev);
    ShellInstance shell = ShellInstance(console);
    shell.Start();

    // Console readkey sample
    /*logger.Info(u"Press any key to continue\n");
    EFI_EVENT waitForKey = system->ConIn->WaitForKey;
    UINTN idx;
    system->BootServices->WaitForEvent(1, &waitForKey, &idx);
    logger.Info(u"Yay\n");
    */

    // Timer sample
    /*while(1)
    {
        system->BootServices->Stall(1000000);
        system->RuntimeServices->GetTime(&time, &caps);
        logger.Info(u"Time: %d-%d-%d %d:%d:%d\n", time.Year, time.Month, time.Day, time.Hour, time.Minute, time.Second);
    }*/

    // Timer sample
    /*
    EFI_EVENT TimerEvent;
    UINTN Index;
    EFI_GUID guid;


    EFI_STATUS createStatus = system->BootServices->CreateEventEx(EVT_TIMER, 0, nullptr, nullptr, &guid, &TimerEvent);
    logger.Info(u"createStatus: %d\n", createStatus);
    EFI_STATUS setStatus = system->BootServices->SetTimer(TimerEvent, TimerRelative, 50000000);
    logger.Info(u"setStatus: %d\n", setStatus);
    logger.Info(u"Waiting\n");
    system->BootServices->WaitForEvent(1, &TimerEvent, &Index);
    logger.Info(u"Done\n");
    */

    /*uchar buf[80];
    memset(buf, 0, sizeof(buf));
    int pos = 0;
    EFI_INPUT_KEY key;
    UINTN idx;
    while (1) {
        system->BootServices->WaitForEvent(1, &system->ConIn->WaitForKey, &idx);
        EFI_STATUS status = system->ConIn->ReadKeyStroke(system->ConIn, &key);
        if (status == EFI_NOT_READY)
            continue;
        if (key.UnicodeChar == 0) {
            pos--;
            buf[pos] = 0;
        }
        else {
            //snprintf(buf, 16, u"%d", key.UnicodeChar);
            buf[pos] = key.UnicodeChar;
            pos++;
            if (pos >= sizeof(buf))
                pos = 0;
        }

        system->ConOut->ClearScreen(system->ConOut);
        system->ConOut->OutputString(system->ConOut, buf);
        system->BootServices->Stall(1000);
    }
    */
    log_panic(system, u"Kernel initialized, waiting in hot loop");

    return EFI_SUCCESS;
}