// FUNC_NAME: HardwareInfo::reportHardwareStatus
// Address: 0x0056a740
// Reports hardware info (OS/CPU?) and free disk space via message system.

#include <windows.h>
#include <stdio.h>

class HardwareInfo {
public:
    void reportHardwareStatus();
};

// Global message system object pointer (likely singleton)
extern HardwareInfo* g_pHardwareInfoManager;

// External helper: returns some hardware info string (e.g., OS version)
extern const char* getHardwareString();

// Global conversion factor (probably bytes to MB or GB)
extern float g_bytesToDisplayUnits;

void HardwareInfo::reportHardwareStatus()
{
    // vtable pointer of this object for sending messages
    int* vtable = *(int**)this;

    // First, send OS/hardware info message
    // "HDWR" = hardware, "OPSY" = operating system
    const char* sysInfo = getHardwareString();
    typedef void (__fastcall* SendMsgFn)(int, int, int, const char*);
    SendMsgFn sendMsg = (SendMsgFn)(vtable[5]); // offset +0x14 = 5th entry (0-based)
    sendMsg(0x48445752, 0x4f505359, sysInfo);   // "HDWR", "OPSY", sysInfo

    // Now get free disk space on current drive (NULL = current directory)
    float freeSpaceMB = 0.0f;
    ULARGE_INTEGER freeBytesAvailable;
    BOOL success = GetDiskFreeSpaceExA(NULL, &freeBytesAvailable, NULL, NULL);
    if (success) {
        // Convert bytes to display units (e.g., MB: divide by 1024*1024)
        freeSpaceMB = (float)(__int64)freeBytesAvailable * g_bytesToDisplayUnits;
    }

    // Format and send disk space message
    char buffer[16]; // 15 chars + null terminator
    _snprintf(buffer, sizeof(buffer), "%f", (double)freeSpaceMB);
    buffer[15] = '\0'; // ensure null termination

    // "HDWR", "HDSP" = hardware disk space
    sendMsg = (SendMsgFn)(*(int**)g_pHardwareInfoManager)[5]; // same vtable offset
    sendMsg(0x48445752, 0x48445350, buffer);   // "HDWR", "HDSP", buffer
}