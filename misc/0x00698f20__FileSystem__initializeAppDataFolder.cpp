// FUNC_NAME: FileSystem::initializeAppDataFolder
// Function address: 0x00698f20
// This function creates or retrieves the standard application data folder path and initializes file system paths.

int FileSystem::initializeAppDataFolder(int folderType, void* unusedParam2, wchar_t** subFolderName, void* unusedParam4, char createFlag)
{
    uint32 csidl;                    // CSIDL value for SHGetFolderPathAndSubDirW
    int32 hresult;                   // HRESULT from SHGetFolderPathAndSubDirW
    wchar_t* folderPath = *subFolderName;  // +0x00: pointer to wide string folder name (or default)
    wchar_t* defaultFolder = &DAT_00e2df14; // default subfolder string (global)
    wchar_t outputPath[256];         // buffer for the full path (512 bytes as wchar_t[256])

    // If no subfolder name provided, use default
    if (folderPath == nullptr) {
        folderPath = defaultFolder;
    }

    // Map folderType to CSIDL
    switch (folderType) {
        case 0: csidl = 0x23; break;  // CSIDL_LOCAL_APPDATA (local application data)
        case 1: csidl = 0x1c; break;  // CSIDL_APPDATA (roaming application data)
        case 2: csidl = 0x2e; break;  // CSIDL_COMMON_APPDATA (common application data)
        case 3: csidl = 5;     break;  // CSIDL_PERSONAL (My Documents)
        default: csidl = 0xFFFFFFFF;  // invalid
    }

    // If createFlag is set, add CSIDL_FLAG_CREATE (0x8000)
    if (createFlag != '\0') {
        csidl |= 0x8000;
    }

    // Retrieve the Windows special folder path with subfolder
    hresult = SHGetFolderPathAndSubDirW(nullptr, csidl, nullptr, 0, folderPath, outputPath);
    if (hresult == 0) {  // S_OK
        // Convert path to some internal format (likely ANSI)
        // auStack_220 is a temporary buffer for conversion
        // FUN_004dbef0: initialize a string converter
        // FUN_004dba00: perform conversion to ANSI
        // These functions are part of the EARS string library

        // Get the current global file system object (singleton)
        // FUN_006984f0 returns pointer to some structure (possibly FileSystem instance)
        void* fsObject = FUN_006984f0();   // returns a pointer to a globally allocated structure

        // Compare with saved stack pointer (likely a check for previous initialization)
        // This seems to be a decompilation artifact; in reality it checks if this is the first call
        if (puStack_8 != fsObject) {        // puStack_8 is uninitialized; might be a global state flag
            // Set the folder path into the file system object
            // FUN_004dbb10(widePath, 0, flags) - sets the application data path
            wchar_t* currentFolder = *(wchar_t**)fsObject;
            if (currentFolder == nullptr) {
                currentFolder = defaultFolder;
            }
            FUN_004dbb10(currentFolder, 0, *(int*)((char*)fsObject + 4));  // +0x04 might be flags
        }

        // Clean up temporary folder string if it was allocated
        if (folderPath != nullptr) {
            // This likely frees the subfolder path if it was dynamically allocated
            // pcStack_224 is actually a function pointer stored on stack for cleanup
            (*pcStack_224)(folderPath);   // This looks like a stack-based cleanup; might be a callback
        }

        // If there is something else to free (iVar7 and pcVar8)
        if (iVar7 != 0) {
            (*pcVar8)(iVar7);
        }

        // Initialize the file system (mount paths, etc.)
        FUN_004dd3c0();

        return 1;  // success
    }

    return 0;  // failure
}