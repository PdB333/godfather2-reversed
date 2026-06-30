// FUNC_NAME: getOSVersion
// Function: 0x006a17c0 - Detects Windows OS version and returns an identifier.
// Returns: 0 = Windows 2000, 1 = Windows XP, 2 = Windows Server 2003, 3 = Windows Vista/7/8/10, -1 = unknown.
int getOSVersion(void)
{
    OSVERSIONINFOA osVersionInfo;
    BOOL success;

    osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA); // 0x94 = 148 bytes
    success = GetVersionExA(&osVersionInfo);
    if (success == FALSE) {
        // error: unable to get OS version
        FUN_006a1760("Unable to get the current operating system version:");
        // Note: FUN_006a1760 likely prints an error message, then function continues?
        // It may not return? But the original code doesn't return after that, so we assume fallthrough.
    }

    // Interpret version numbers
    if (osVersionInfo.dwMajorVersion == 5) {
        switch (osVersionInfo.dwMinorVersion) {
            case 0: // Windows 2000
                return 0;
            case 1: // Windows XP
                return 1;
            case 2: // Windows Server 2003
                return 2;
            default:
                break;
        }
    } else if (osVersionInfo.dwMajorVersion == 6) {
        // Windows Vista (6.0), Windows 7 (6.1), Windows 8 (6.2), Windows 10 (6.3+)
        return 3;
    }

    return -1; // unknown OS version
}