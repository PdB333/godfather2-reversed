// FUNC_NAME: FileManager::loadTextAsset
// Address: 0x00605690
// Role: Loads a text file asset by index, allocates a null-terminated buffer via an allocator, and returns the buffer along with its size.

int FileManager::loadTextAsset(Allocator* pAllocator, uint* pOutSize) {
    // Stack probe or debug allocation (0x80 bytes) - often a checkpoint or memory guard
    FUN_00401aa0(0x80);

    // Global file manager singleton
    FileManager* pFileMgr = (FileManager*)DAT_01223378;

    // Open file by index 1? (local buffer for path?)
    int fileHandle = FUN_004015e0(local_88, 1);
    if (fileHandle != 0) {
        // Get file size from a table at pFileMgr+0x38, entry size 0x10, size at offset 0x0C
        // +0x38: pointer to array of file info structures (each 0x10 bytes)
        // +0x0C: size field
        uint fileSize = *(uint*)(*(int*)((int)pFileMgr + 0x38) + 0x0C + fileHandle * 0x10);
        *pOutSize = fileSize;

        // Allocator parameters: flags=2, align=0x10, unknown=0
        AllocParams params;
        params.flags = 2;
        params.alignment = 0x10;
        params.unknown = 0;

        // Allocate buffer via allocator's first virtual function (operator new)
        int buffer = (pAllocator->vtable->allocate)(pAllocator, fileSize + 1, &params);

        // Read file content into buffer; returns actual bytes read
        uint bytesRead = FUN_00401780(fileHandle, buffer, unaff_EBX);

        // Close file handle
        FUN_004016d0(fileHandle);

        // Check if read succeeded (bytesRead >= expected size)
        if (*pOutSize <= bytesRead) {
            // Null-terminate the string at the expected position
            *(char*)(*pOutSize + buffer) = '\0';
            return buffer;
        }

        // Read failed: free buffer via allocator's second virtual function (operator delete)
        if (buffer != 0) {
            (pAllocator->vtable->free)(pAllocator, buffer, 0);
        }
        *pOutSize = 0;
    }
    return 0;
}