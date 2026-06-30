// FUNC_NAME: registerDeviceInterfaceNotification
// Function address: 0x0069d680
// Role: Registers for device interface change notifications (e.g., input device arrival/removal)
// Calls RegisterDeviceNotificationA with a populated DEV_BROADCAST_DEVICEINTERFACE structure

#include <windows.h>

// Structure for device interface notification broadcast (Win32)
// typedef struct _DEV_BROADCAST_DEVICEINTERFACE {
//     DWORD dbcc_size;          // 0x00
//     DWORD dbcc_devicetype;    // 0x04 (DBT_DEVTYP_DEVICEINTERFACE = 5)
//     DWORD dbcc_reserved;      // 0x08
//     GUID  dbcc_classguid;     // 0x0C (16 bytes)
//     char  dbcc_name[1];       // 0x1C (variable)
// } DEV_BROADCAST_DEVICEINTERFACE, *PDEV_BROADCAST_DEVICEINTERFACE;

void registerDeviceInterfaceNotification(HANDLE hWnd, unsigned long long guidPart1, unsigned long long guidPart2)
{
    // Build the DEV_BROADCAST_DEVICEINTERFACE on the stack
    DEV_BROADCAST_DEVICEINTERFACE notifyFilter;
    ZeroMemory(&notifyFilter, sizeof(notifyFilter));

    notifyFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);  // 0x20
    notifyFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;       // 5

    // Copy the GUID halves into the structure's classguid field
    CopyMemory(&notifyFilter.dbcc_classguid, &guidPart1, sizeof(guidPart1));
    CopyMemory((reinterpret_cast<char*>(&notifyFilter.dbcc_classguid) + sizeof(guidPart1)),
               &guidPart2, sizeof(guidPart2));

    // notifyFilter.dbcc_name[0] remains '\0' because we zero-initialized

    RegisterDeviceNotificationA(hWnd, &notifyFilter, 0);
}