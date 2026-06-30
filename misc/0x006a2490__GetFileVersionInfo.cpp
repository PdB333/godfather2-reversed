// FUNC_NAME: GetFileVersionInfo
// Function address: 0x006a2490
// Extracts the 4-part version number (major.minor.release.build) from the current executable's version resource.

typedef unsigned int uint;

uint* GetFileVersionInfo(uint* outVersion)
// outVersion must point to an array of 4 uint values.
// Returns outVersion filled with [major, minor, release, build].
{
    // Zero the output array initially.
    outVersion[0] = 0;
    outVersion[1] = 0;
    outVersion[2] = 0;
    outVersion[3] = 0;

    // Get the path of the current executable.
    HMODULE hModule = GetModuleHandleA(nullptr);
    char filePath[512];
    GetModuleFileNameA(hModule, filePath, 512);

    // Retrieve the version information resource.
    byte versionInfoBuffer[512];
    GetFileVersionInfoA(filePath, 0, 512, versionInfoBuffer);

    // Query the root block to obtain the VS_FIXEDFILEINFO structure.
    LPVOID fixedInfoPtr;
    BOOL success = VerQueryValueA(versionInfoBuffer, "\\", &fixedInfoPtr, nullptr);
    if (success != 0)
    {
        // Extract the version components from the VS_FIXEDFILEINFO structure.
        // Offsets (little-endian): 
        // +0x08: dwFileVersionMS (major<<16 | minor)
        // +0x0C: dwFileVersionLS (release<<16 | build)
        ushort minor = *(ushort*)((int)fixedInfoPtr + 8);   // low word of dwFileVersionMS
        ushort major = *(ushort*)((int)fixedInfoPtr + 10);  // high word of dwFileVersionMS
        ushort build = *(ushort*)((int)fixedInfoPtr + 14);  // high word of dwFileVersionLS
        ushort release = *(ushort*)((int)fixedInfoPtr + 12); // low word of dwFileVersionLS

        outVersion[0] = (uint)major;
        outVersion[1] = (uint)minor;
        outVersion[2] = (uint)release;
        outVersion[3] = (uint)build;
    }

    return outVersion;
}