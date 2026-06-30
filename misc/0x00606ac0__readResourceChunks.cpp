// FUNC_NAME: readResourceChunks

int __thiscall readResourceChunks(void* buffer, uint resourceIndex, int bufferSize)
{
    int iVar1;
    int chunkSize;
    int i;
    int remaining;

    // Resource index must be less than 4096 (0x1000)
    if ((resourceIndex < 0x1000) && (iVar1 = (int)(resourceIndex * 0x38), iVar1 != -0x11a0f28)) {
        i = 0;
        remaining = bufferSize;
        // Global table at 0x011a0f29, each entry 0x38 bytes, first byte = number of chunks
        if (*(byte *)(0x011a0f29 + iVar1) == 0) {
            return 0;
        }
        do {
            chunkSize = FUN_00606a40(); // Read next chunk, returns bytes read or -1
            if (chunkSize == -1) {
                return 0;
            }
            if (buffer != (void *)0x0) {
                remaining = remaining - chunkSize;
                buffer = (void *)((int)buffer + chunkSize);
            }
            i = i + 1;
        } while (i < (int)*(byte *)(0x011a0f29 + iVar1));
        return bufferSize - remaining; // Total bytes read
    }
    return -1;
}