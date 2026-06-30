// FUNC_NAME: MemoryPool::allocateAndCopy
void __fastcall MemoryPool::allocateAndCopy(undefined4* source1, undefined8* source2)
{
    // Local buffer to combine the two data sources (64 bytes from source1 + 96 bytes from source2 = 160 bytes)
    undefined4 localBuffer[40]; // 160 bytes as 40 dwords
    undefined8* localBufferQwords = (undefined8*)localBuffer;

    // Copy first source (16 dwords = 64 bytes) into buffer
    localBuffer[0] = *source1;
    localBuffer[1] = source1[1];
    localBuffer[2] = source1[2];
    localBuffer[3] = source1[3];
    localBuffer[4] = source1[4];
    localBuffer[5] = source1[5];
    localBuffer[6] = source1[6];
    localBuffer[7] = source1[7];
    localBuffer[8] = source1[8];
    localBuffer[9] = source1[9];
    localBuffer[10] = source1[10];
    localBuffer[11] = source1[11];
    localBuffer[12] = source1[12];
    localBuffer[13] = source1[13];
    localBuffer[14] = source1[14];
    localBuffer[15] = source1[15];

    // Copy second source (12 qwords = 96 bytes) into buffer after the first 64 bytes
    localBufferQwords[8] = *source2;
    localBufferQwords[9] = source2[1];
    localBufferQwords[10] = source2[2];
    localBufferQwords[11] = source2[3];
    localBufferQwords[12] = source2[4];
    localBufferQwords[13] = source2[5];
    localBufferQwords[14] = source2[6];
    localBufferQwords[15] = source2[7];
    localBufferQwords[16] = source2[8];
    localBufferQwords[17] = source2[9];
    localBufferQwords[18] = source2[10];
    localBufferQwords[19] = source2[11];

    // Allocator state: global pointer at DAT_01206880 + 0x14 holds current allocation position
    int* allocatorPtr = (int*)(DAT_01206880 + 0x14);

    // Write vtable pointer at the current allocation address
    *(void***)*allocatorPtr = &PTR_LAB_01126d48;

    // Advance allocator pointer past the vtable (4 bytes)
    *allocatorPtr = *allocatorPtr + 4;

    // Align destination to 16-byte boundary
    void* alignedDest = (void*)((*allocatorPtr + 0xf) & ~0xf);
    *allocatorPtr = (int)alignedDest;

    // Copy the 160-byte combined buffer to the aligned destination
    _memcpy(alignedDest, &localBuffer[0], 0xa0);

    // Advance allocator pointer by the copied size
    *allocatorPtr = *allocatorPtr + 0xa0;
}