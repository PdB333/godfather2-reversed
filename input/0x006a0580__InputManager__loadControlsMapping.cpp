// FUNC_NAME: InputManager::loadControlsMapping
// Address: 0x006a0580
// This function loads the controls mapping from "controls.rmp" saved in the user's documents folder.
// It uses a global state pointer (g_gameState) at 0x01129828, with offsets 0x2264 and 0x2260
// for the target data structure.

#include <shlobj.h>   // for SHGetFolderPathAndSubDirW
#include <windows.h>

// Forward declarations for internal engine helpers
// Engine wide-string management functions (assumed)
void* __cdecl FUN_004dbef0(); // returns a string object
void* __cdecl FUN_004dba00(void* a); // manipulates string
void* __cdecl FUN_00699080(wchar_t* a, wchar_t* b, int c); // path concatenation
void  __cdecl FUN_004dbf70(wchar_t* a, int b, int c, int d); // unknown
void  __cdecl FUN_004dbd90(void* dst, int size, int flag); // string copy/initialization
void  __cdecl FUN_004dbb10(wchar_t* a, int b, int c); // memory free
void  __cdecl FUN_00497620(wchar_t* a); // cleanup
void  __cdecl FUN_006a0430(); // error handler / abort

// Global game state pointer (from other functions)
extern uint8_t* g_gameState; // DAT_01129828

void InputManager::loadControlsMapping()
{
    wchar_t* pControlsFilePath = (wchar_t*)PTR_u_controls_rmp_00e50c74; // pointer to "controls.rmp" wide string constant
    wchar_t* tempStr;
    int ret;
    wchar_t* combinedPath;
    wchar_t* outPathBuffer;

    // Check if the target data structure at offset 0x2264 is null (indicates not yet initialized)
    if (*(int*)(g_gameState + 0x2264) == 0x0) {
        FUN_006a0430(); // abort or initialize
        return;
    }

    // First, get the documents folder path using SHGetFolderPathAndSubDirW
    // Setup stack variables for the call (parameters pushed in reverse order)
    // The actual call is SHGetFolderPathAndSubDirW(NULL, CSIDL_PERSONAL, NULL, 0, &basePath, &subDir, &fullPath)
    // But decompiler shows only one explicit arg; we reconstruct from stack assignments
    wchar_t* subDir = (wchar_t*)PTR_u_controls_rmp_00e50c74; // "controls.rmp"
    wchar_t* basePath = 0; // will be set by the API
    wchar_t* fullPath = 0; // will be set by the API

    // Stack setup: (approximate from the decompiled assignment order)
    // puStack_260 -> basePath buffer (out)
    // uStack_25c -> flags? maybe 0
    // ppcStack_258 -> NULL (hwnd)
    // pcStack_254 -> subDir (subfolder, e.g., "controls.rmp")
    // Not fully reconstructible, but the call is:
    ret = SHGetFolderPathAndSubDirW(
        NULL,               // hwnd = 0
        CSIDL_PERSONAL | CSIDL_FLAG_CREATE, // csidl (0x8005)
        NULL,               // hToken
        0,                  // dwFlags
        &basePath,          // pszPath (maybe out)
        subDir,             // pszSubDir (subfolder to append, e.g. "controls.rmp")
        &fullPath);         // pszPath (result)

    if (ret != 0) {
        // Failed to get folder path
        FUN_006a0430();
    }
    else {
        // Success: now process the full path (fullPath is now a wide string)
        // There are several cleanups and copies; simplified:
        // Initialize a temporary object (maybe a std::wstring) from fullPath
        FUN_004dbf70(&DAT_00e36ef4, 1, iStack_240, uStack_23c); // unclear

        // Copy fullPath into a local buffer
        FUN_004dbd90(local_208, 0, unaff_EDI); // local_208 is a wchar_t buffer (520 bytes)

        // If local_208 not null, call some function on it (free?)
        if (local_208 != 0) {
            (*pcStack_244)(local_208);
        }

        // Build the final path using FUN_00699080 with subDir and some base
        // This likely concatenates the documents folder and "controls.rmp"
        // puStack_260 is the base path from SHGetFolderPath
        combinedPath = FUN_00699080(&stack0xfffffdb0, puStack_260, 3);

        if (&puStack_260 != &combinedPath) {
            tempStr = *combinedPath;
            if (tempStr == 0) {
                tempStr = &DAT_00e2df14; // empty string
            }
            // Copy combinedPath into some structure
            FUN_004dbb10(tempStr, 0, combinedPath[1]);
        }

        if (local_208 != 0) {
            (*pcStack_244)(local_208);
        }

        tempStr = puStack_260;
        if (tempStr == 0) {
            tempStr = &DAT_00e2df14;
        }
        // Finalize: store the path or process the mapping file
        FUN_00497620(tempStr);
    }

    // Cleanup: free various temporary objects
    if (iStack_230 != 0) {
        (*pcStack_224)(iStack_230);
    }
    if (puStack_260 != 0) {
        (*pcStack_254)(puStack_260);
    }
    if (iStack_240 != 0) {
        (*pcStack_234)(iStack_240);
    }

    return;
}