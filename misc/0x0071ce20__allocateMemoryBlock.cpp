// FUNC_NAME: allocateMemoryBlock
int allocateMemoryBlock() {
    int returnValue = 0;
    void* pBuffer = nullptr;
    // Call virtual function on global allocator instance at DAT_0112ad34
    // This allocates 0x40 (64) bytes and stores pointer in pBuffer.
    int allocResult = (*(int (__cdecl**)(int, void**))(*DAT_0112ad34))(0x40, &pBuffer);
    if (allocResult != 0) {
        returnValue = initializeAllocatedBlock(); // FUN_0071c030
    }
    releaseAllocatedBlock(&pBuffer); // FUN_0071cd20, pass address of pointer
    return returnValue;
}