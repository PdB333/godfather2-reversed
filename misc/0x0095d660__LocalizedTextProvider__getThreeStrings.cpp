// FUNC_NAME: LocalizedTextProvider::getThreeStrings
// Address: 0x0095d660
// Role: Extracts three localized strings from internal resource IDs (stored at +0x14, +0x18, +0x1c)
//       and copies them into the provided output buffers using a safe copy function.
// Calls:
//   FUN_00604000 (getStringResource1) - first string resource lookup
//   FUN_00603d30 (getStringResource2) - second/third string resource lookup
//   FUN_005c4660 (safeStringCopy) - bounded string copy

void __thiscall LocalizedTextProvider::getThreeStrings(
    int this,
    char* out1,
    char* out2,
    char* out3,
    int maxLen                      // maximum length for each copy
)
{
    char* tempStr = 0;             // +0x00 local_10
    int flags = 0;                 // +0x04 local_c (unused, passed as 0)
    int extra = 0;                 // +0x08 local_8 (unused)
    void (*cleanupFunc)(char*) = 0; // +0x0c local_4 (likely a free function, but null in this context)

    // Retrieve first string from resource ID at this+0x14
    getStringResource1(*(int*)(this + 0x14), &tempStr, 1); // 1 = allocate?
    const char* src = tempStr;
    if (src == 0) {
        src = ""; // DAT_0120546e (empty string placeholder)
    }
    safeStringCopy(out1, src, maxLen, flags); // copy into output

    // Retrieve second string from resource ID at this+0x18
    getStringResource2(*(int*)(this + 0x18), &tempStr, 1);
    src = tempStr;
    if (src == 0) {
        src = "";
    }
    safeStringCopy(out2, src, maxLen, flags);

    // Retrieve third string from resource ID at this+0x1c
    getStringResource2(*(int*)(this + 0x1c), &tempStr, 1);
    src = tempStr;
    if (src == 0) {
        src = "";
    }
    safeStringCopy(out3, src, maxLen, flags);

    // Cleanup the last allocated string (if any) using a function pointer.
    // In the decompiled output cleanupFunc is null, so this would crash.
    // It is likely a decompilation artifact or an unused function pointer member.
    if (tempStr != 0) {
        cleanupFunc(tempStr); // potentially a free or release call
    }
}