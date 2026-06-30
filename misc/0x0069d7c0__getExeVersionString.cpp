// FUNC_NAME: getExeVersionString
// Address: 0x0069d7c0
// Purpose: Retrieves the executable's version number and stores it in global gGameVersionString.

#include <windows.h>
#include <cstdio>

// Global buffer at 0x01129fc0 (100 bytes)
char gGameVersionString[100] = {};

void getExeVersionString()
{
    char exePath[MAX_PATH];
    DWORD verSize = 0;
    void* verBuf = nullptr;
    VS_FIXEDFILEINFO* pFileInfo = nullptr;
    UINT uLen = 0;

    // Get the executable module path
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);

    // Retrieve the size of version info
    verSize = GetFileVersionInfoSizeA(exePath, nullptr);
    if (verSize == 0)
        return;

    // Allocate buffer for version info
    verBuf = malloc(verSize);
    if (!verBuf)
        return;

    // Retrieve version info
    if (GetFileVersionInfoA(exePath, 0, verSize, verBuf))
    {
        // Query the root block (VS_FIXEDFILEINFO)
        if (VerQueryValueA(verBuf, "\\", (LPVOID*)&pFileInfo, &uLen) && pFileInfo)
        {
            DWORD ms = pFileInfo->dwFileVersionMS;
            DWORD ls = pFileInfo->dwFileVersionLS;

            // Extract version components: major.minor.build.revision
            int major   = HIWORD(ms);
            int minor   = LOWORD(ms);
            int build   = HIWORD(ls);
            int revision = LOWORD(ls);

            // Format and store into global buffer
            sprintf_s(gGameVersionString, sizeof(gGameVersionString),
                      "%d.%d.%d.%d", major, minor, build, revision);
        }
    }

    free(verBuf);
}