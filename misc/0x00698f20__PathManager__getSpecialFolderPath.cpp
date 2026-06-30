// FUNC_NAME: PathManager::getSpecialFolderPath
int PathManager::getSpecialFolderPath(
    uint folderId,
    uint unused1,           // not used in this function
    wchar_t** subFolder,    // pointer to subfolder path, may be null
    uint unused2,           // not used in this function
    bool createIfMissing
) {
    uint csidl = 0xFFFFFFFF;
    switch (folderId) {
    case 0:
        csidl = 0x23;    // CSIDL_COMMON_APPDATA
        break;
    case 1:
        csidl = 0x1c;    // CSIDL_LOCAL_APPDATA
        break;
    case 2:
        csidl = 0x2e;    // CSIDL_COMMON_DOCUMENTS
        break;
    case 3:
        csidl = 5;       // CSIDL_PERSONAL (My Documents)
        break;
    default:
        break;
    }

    if (createIfMissing) {
        csidl |= 0x8000; // CSIDL_FLAG_CREATE
    }

    wchar_t* subFolderPath = (subFolder ? *subFolder : nullptr);
    if (subFolderPath == nullptr) {
        subFolderPath = g_emptyWideString; // DAT_00e2df14
    }

    wchar_t buffer[256]; // local_208, size 512 bytes for wide chars
    // Actually buffer size is 512 bytes = 256 wchar_t
    int hr = SHGetFolderPathAndSubDirW(nullptr, csidl, nullptr, 0, subFolderPath, buffer);
    if (hr == 0) {
        // Success
        // FUN_004dbef0 and FUN_004dba00 seem to be string operations on auStack_220
        // They are likely path concatenation or initialization
        void* stackBuffer = auStack_220; // 24-byte buffer (12 wchar_t?)
        uint length = FUN_004dbef0(stackBuffer);
        FUN_004dba00(stackBuffer, length);

        // FUN_006984f0 returns a global singleton (e.g., application or path manager)
        PathManager* pathMgr = (PathManager*)FUN_006984f0();
        if (stackBuffer != pathMgr) {
            // Compare addresses (stack vs global) – this is always true?
            wchar_t* defaultSubfolder = (wchar_t*)*pathMgr;
            if (defaultSubfolder == nullptr) {
                defaultSubfolder = g_emptyWideString;
            }
            // FUN_004dbb10 likely sets a base path using the subfolder and a flag
            FUN_004dbb10(defaultSubfolder, 0, pathMgr[1]); // second member of pathMgr
        }

        if (subFolderPath != nullptr) {
            (*(void(*)(wchar_t*))pcStack_224)(subFolderPath); // likely frees the subfolder string?
        }
        if (iVar7 != 0) {
            (*(void(*)(int))pcVar8)(iVar7);
        }

        FUN_004dd3c0(); // Finalization or cleanup
        return 1;
    }
    return 0;
}