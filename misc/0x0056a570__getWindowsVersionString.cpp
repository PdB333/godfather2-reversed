// FUNC_NAME: getWindowsVersionString
static const char* getWindowsVersionString() {
    OSVERSIONINFOEXA versionInfo;
    memset(&versionInfo.dwMajorVersion, 0, sizeof(versionInfo) - sizeof(versionInfo.dwOSVersionInfoSize));
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);

    if (GetVersionExA((LPOSVERSIONINFOA)&versionInfo) != FALSE) {
        // Major version 5 = Windows 2000/XP
        if (versionInfo.dwMajorVersion == 5) {
            // Minor version != 0 means XP (5.1) rather than 2000 (5.0)
            if (versionInfo.dwMinorVersion != 0) {
                // Check suite mask for Personal (Home) or Workstation (Pro)
                if ((versionInfo.wSuiteMask & VER_SUITE_PERSONAL) != 0) {
                    return "xp_home";
                }
                // VER_NT_WORKSTATION is 0x1 in wProductType
                if (versionInfo.wProductType == VER_NT_WORKSTATION) {
                    return "xp_pro";
                }
            }
            // Windows 2000 or unknown variant – fall through to unknown
        }
        // Major version 6 = Windows Vista / 7 / 8 (but game era is Vista)
        else if (versionInfo.dwMajorVersion == 6) {
            return "vista";
        }
    }
    return "unknown";
}