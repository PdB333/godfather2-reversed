// FUNC_NAME: FileManager::processFileHandle
uint FileManager::processFileHandle(FileManager* this, uint fileHandle) {
    bool bIsValid = false;
    int fileDesc;
    uint result = fileHandle;

    if (fileHandle != 0) {
        // Check if file handle is open and valid
        fileDesc = isFileOpen(fileHandle, 0); // FUN_00445ff0
        if (fileDesc == 0) {
            int typeCheck = isFileValid(fileHandle, 0); // FUN_004461c0
            if (typeCheck != 0) {
                uint magic = getFileMagic(); // FUN_0043aaf0
                if (magic == 0x602b23f0) {
                    // Clear low byte of handle (flags/offset mask)
                    uint flagsVar = fileHandle & 0xffffff00;
                    int flagsResult = getFileFlags(fileHandle, &flagsVar); // FUN_00448100
                    if ((char)flagsVar == '\0' && flagsResult != 0) {
                        bIsValid = true;
                    }
                }
            }
        }

        // Retrieve a file handler object (vtable-based)
        void* fileHandler = nullptr;
        char findRes = findFileHandler(fileDesc, 0x33ea0946, &fileHandler); // FUN_004480d0
        if (findRes != 0) {
            // Call virtual method at offset 0x20 (likely getDataSize)
            result = (*(uint (__thiscall**)(FileManager*))(*((int*)fileHandler) + 0x20))(this);
        }

        // Check flags at offset 0x14 in file descriptor for a pending close or lock bit (0x8000000)
        if (bIsValid && fileDesc != 0 && (*(uint*)(fileDesc + 0x14) & 0x8000000) != 0) {
            releaseLock(fileDesc + 0x3c); // FUN_004088c0 (cleanup)
        }
    }
    return result;
}