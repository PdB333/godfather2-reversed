// FUNC_NAME: FileReadState::readNextBlock
// Address: 0x00697ed0
// Reads a block of data from a file: first reads a 4-byte header, then reads the remaining data based on total size.
// Returns 8 on success, 0 on failure. Outputs a bool flag indicating whether more data remains.

int __thiscall FileReadState::readNextBlock(LPVOID this, DWORD *pBytesReadAndFlag)
{
    DWORD bytesRead;
    int *allocPtr;
    BOOL success;
    int remainingSize;
    LPVOID buffer;
    int result;
    bool hasMoreData;

    hasMoreData = (*(int *)((int)this + 0x28) != 0); // +0x28: remaining bytes in current block?
    *pBytesReadAndFlag = (DWORD)hasMoreData;
    if (!hasMoreData) {
        return 8; // no more data, but success?
    }

    allocPtr = (int *)FUN_009c8e50(8); // allocate 8-byte header
    if (allocPtr == (int *)0x0) {
        allocPtr = (int *)0x0;
    } else {
        *allocPtr = 4;                      // header size field?
        *(short *)(allocPtr + 1) = 0;       // +4: short
        *(short *)((int)allocPtr + 6) = 0;  // +6: short
    }
    *(int **)((int)this + 0x14) = allocPtr; // +0x14: pointer to header

    success = ReadFile(*(HANDLE *)((int)this + 0x18), // +0x18: file handle
                      this, 4, &bytesRead, NULL);
    if (success != 0) {
        remainingSize = *(int *)((int)this + 0x24) - bytesRead; // +0x24: total size of block?
        *(int *)((int)this + 0x28) = remainingSize;            // update remaining

        buffer = (LPVOID)FUN_009c8e80(remainingSize); // allocate data buffer
        *(LPVOID *)((int)this + 0x2c) = buffer;      // +0x2c: data buffer

        success = ReadFile(*(HANDLE *)((int)this + 0x18),
                          buffer, *(DWORD *)((int)this + 0x28), &bytesRead, NULL);
        if (success != 0) {
            int dataPtr = *(int *)((int)this + 0x2c);
            *(int *)((int)this + 0x14) = dataPtr;               // header pointer updated to data
            *(int *)((int)this + 0x30) = dataPtr + 8;           // +0x30: pointer after 8-byte header in data?
            result = FUN_00ab8560(0, dataPtr, *(int *)((int)this + 0x28)); // process/uncompress?
            *(int *)((int)this + 0x1c) = result;                // +0x1c: result of processing
            *(int *)((int)this + 0x28) = *(int *)((int)this + 0x28) - bytesRead;
            *(bool *)pBytesReadAndFlag = (*(int *)((int)this + 0x28) != 0);
            return 8;
        }
    }
    return 0;
}