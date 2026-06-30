// FUNC_NAME: getWindowsVersion
// Function address: 0x006a17c0
// Role: Detects the Windows operating system version and returns an identifier.
// Returns: 0 = Windows 2000 (5.0), 1 = Windows XP (5.1), 2 = Windows Server 2003 (5.2), 3 = Windows Vista/7 (6.x), -1 = unknown or error.

int getWindowsVersion(void)
{
    BOOL success;
    OSVERSIONINFOA osVersionInfo;

    osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    success = GetVersionExA(&osVersionInfo);
    if (success == FALSE) {
        FUN_006a1760("Unable to get the current operating system version:");
    }
    else {
        if (osVersionInfo.dwMajorVersion == 5) {
            if (osVersionInfo.dwMinorVersion == 0) {
                return 0; // Windows 2000
            }
            if (osVersionInfo.dwMinorVersion == 1) {
                return 1; // Windows XP
            }
            if (osVersionInfo.dwMinorVersion == 2) {
                return 2; // Windows Server 2003 / XP x64
            }
        }
        else if (osVersionInfo.dwMajorVersion == 6) {
            return 3; // Windows Vista, 7, 8, etc.
        }
    }
    return 0xFFFFFFFF; // -1, unknown or error
}