// FUNC_NAME: openAutomateInit
#include <windows.h> // for LoadLibraryW, GetProcAddress, MultiByteToWideChar, GetLastError, DWORD, LPCWSTR, HMODULE, FARPROC
#include <stdio.h>   // for fprintf

// Globals (addresses from Ghidra)
// DAT_0112a0d0: char* pluginPath (ANSI)
// DAT_0112a0d8: HMODULE hModule
// DAT_0112a0c8: FARPROC oaPluginInitProc

extern char* DAT_0112a0d0;       // +0x0
extern HMODULE DAT_0112a0d8;     // +0x8
extern FARPROC DAT_0112a0c8;     // +0xc8? (offsets approximate)

int __cdecl openAutomateInit(void)
{
    char c;
    LPCSTR path = DAT_0112a0d0;
    WCHAR widePath[2048]; // local_1000, size 0x800 wide chars (2046+null? Actually 2046 WCHAR, but we'll use safe size)
    int ret;
    DWORD lastError;

    // Convert ANSI plugin path to wide char
    int converted = MultiByteToWideChar(0xFDE9, 0, path, -1, widePath, 0x800);
    if (converted != 0) {
        // Load the DLL
        DAT_0112a0d8 = LoadLibraryW(widePath);
        if (DAT_0112a0d8 != NULL) {
            // Get the required entry point
            DAT_0112a0c8 = GetProcAddress(DAT_0112a0d8, "oaPluginInit");
            if (DAT_0112a0c8 != NULL) {
                return 1; // Success
            }
            // Entry point not found
            fprintf((FILE*)(FUN_00b995f7() + 0x40), "ERROR: %s\n", "Plugin does not have the correct entry point.");
            DAT_0112a0c8 = NULL; // Clear failed pointer
        } else {
            fprintf((FILE*)(FUN_00b995f7() + 0x40), "OpenAutomate Failed loading: '%s'\n", path);
        }
    } else {
        // MultiByteToWideChar failed
        lastError = GetLastError();
        const char* errorMsg;
        switch (lastError) {
            case 0x7A: // ERROR_INSUFFICIENT_BUFFER
                errorMsg = "OpenAutomate MultiByteToWideChar returned error: ERROR_INSUFFICIENT_BUFFER\n";
                break;
            case 0x3EC: // ERROR_INVALID_FLAGS
                errorMsg = "OpenAutomate MultiByteToWideChar returned error: ERROR_INVALID_FLAGS\n";
                break;
            case 0x57: // ERROR_INVALID_PARAMETER
                errorMsg = "OpenAutomate MultiByteToWideChar returned error: ERROR_INVALID_PARAMETER\n";
                break;
            case 0x459: // ERROR_NO_UNICODE_TRANSLATION
                errorMsg = "OpenAutomate MultiByteToWideChar returned error: ERROR_NO_UNICODE_TRANSLATION\n";
                break;
            default:
                goto checkEmptyPath;
        }
        fprintf((FILE*)(FUN_00b995f7() + 0x40), errorMsg);
    }

checkEmptyPath:
    // If path is empty string, print a specific message
    {
        const char* p = path;
        while (*p != '\0') p++;
        if (p == path + 1) { // only null terminator? Actually path+1 means length 0? Wait: original check "if (pcVar5 == DAT_0112a0d0 + 1)" meaning path+1 (since loop increments after null terminator, points to address after null). So if path is empty (only null), then p == path+1.
            fprintf((FILE*)(FUN_00b995f7() + 0x40), "OpenAutomate PluginPath was undefined\n");
        }
    }

    return 0; // Failure
}