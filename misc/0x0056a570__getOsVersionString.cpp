// FUNC_NAME: getOsVersionString
#include <windows.h>
#include <string.h>

// Returns a string identifying the current Windows OS version: "xp_home", "xp_pro", "vista", or "unknown"
char* getOsVersionString()
{
    OSVERSIONINFOA verInfo;
    memset(&verInfo, 0, sizeof(verInfo));
    verInfo.dwOSVersionInfoSize = sizeof(verInfo); // 0x9c

    if (GetVersionExA(&verInfo))
    {
        // Windows XP (NT 5.1) or Windows Server 2003 (5.2)
        if (verInfo.dwMajorVersion == 5)
        {
            // Skip Windows 2000 (5.0)
            if (verInfo.dwMinorVersion != 0)
            {
                // Check suite mask and product type stored after szCSDVersion
                // Structure offsets: +0x94 wServicePackMajor (2), +0x96 wServicePackMinor (2),
                // +0x98 wSuiteMask (2), +0x9a wProductType (1), +0x9b reserved (1)
                // We access the last 4 bytes as a DWORD (uStack_4)
                DWORD last4 = *(DWORD*)((char*)&verInfo + 0x98);
                if (last4 & 0x200) // VER_SUITE_PERSONAL? (0x200 = 512)
                {
                    return "xp_home";
                }
                // Check byte at offset 0x9a (wProductType)
                if (*(((char*)&verInfo) + 0x9a) == 1) // VER_NT_WORKSTATION
                {
                    return "xp_pro";
                }
            }
        }
        else if (verInfo.dwMajorVersion == 6) // Windows Vista/7
        {
            return "vista";
        }
    }
    return "unknown";
}