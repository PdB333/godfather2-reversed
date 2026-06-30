// FUNC_NAME: CompressionManager::compressData
int __thiscall CompressionManager::compressData(void *this, int dataPtr, int dataSize, char *outputBuf, int outputBufSize)
{
    extern void initCompression();
    extern int compressChunk(char *dest, int destSize);  // param_4+4 and param_5-4
    extern void processData(int a, int b);                // param_2, param_3

    initCompression();
    compressChunk(outputBuf + 4, outputBufSize - 4);
    processData(dataPtr, dataSize);

    // Call virtual function at vtable offset 0x0C with argument 2
    // The vtable is from the object pointed by this+4
    (*(void (**)(void *, int))(**(int **)((char *)this + 4) + 0x0C))((void *)this, 2);

    // Write "CMPR" magic at start of output buffer
    outputBuf[0] = 0x43; // 'C'
    outputBuf[1] = 0x4D; // 'M'
    outputBuf[2] = 0x50; // 'P'
    outputBuf[3] = 0x52; // 'R'

    // Return value: offset 0x18 from the object at this+4, plus 4
    // +0x18 likely compressed data size or end pointer after header
    return *(int *)(*(int *)((char *)this + 4) + 0x18) + 4;
}