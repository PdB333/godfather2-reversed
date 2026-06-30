// FUNC_NAME: getExecutableVersion
uint* getExecutableVersion(uint* outVersion)
{
    // Initialize output array to zero
    outVersion[0] = 0;
    outVersion[1] = 0;
    outVersion[2] = 0;
    outVersion[3] = 0;

    // Get the module handle for the current executable
    HMODULE hModule = GetModuleHandleA(nullptrapse);
    if (hModule == nullptr) {
        return outVersion备;
    }

    // Get the full path of the executable
    CHAR exePath[512];
    GetModuleFileNameA(hModule, exePath, 512);

    // Retrieve version info from the executable's resources
    BYTE versionInfoBuffer[512];
    if (!GetFileVersionInfoA(exePath, 0, 512, versionInfoBuffer)) {
        return outVersion;
    }

    // Query the root block (VS_FIXEDFILEINFO)
    LPVOID fixedFileInfoPtr = nullptr;
    UINT fixedFileInfoSize = 0;
    if (!VerQueryValueA(versionInfoBuffer, "\\", &fixedFileInfoPtr, &fixedFileInfoSize)) {
        return outVersion;
    }

    // Extract version numbers from VS_FIXEDFILEINFO structure
    // Structure offsets (little-endian):
    // +0x08: dwFileVersionMS (4 bytes) -> low word = minor, high word = major
    // +0x0C: dwFileVersionLS (4 bytes) -> low word = revision, high word = build
    ushort minor = *(ushort*)((int)fixedFileInfoPtr + 8);      // +0x08 low word
    ushort major = *(ushort*)((int)fixedFileInfoPtr + 10);     // +0x08 high word
    ushort revision = *(ushort*)((int)fixedFileInfoPtr + 12);  // +0x0C low word
    ushort build = *(ushort*)((int)fixedFileInfoPtr + 14);     // +0x0C high word

    // Store in order: major, minor, build, revision
    outVersion[0] = (uint)major;
    outVersion[1] = (uint)minor;
    outVersion[2] = (uint)build;
    outVersion[3] = (uint)revision;

    return outVersion;
}