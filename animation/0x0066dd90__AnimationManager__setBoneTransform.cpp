// FUNC_NAME: AnimationManager::setBoneTransform

void __fastcall AnimationManager::setBoneTransform(short slotIndex, const float* matrix1, const float* matrix2, const float* vector1, const float* vector2)
{
    // +4: short lastWriteIndex  (last used block index)
    // +6: short nextWriteIndex   (next free block index)
    // +8: short slotIndex        (bone/slot to update)
    // +0x810: pointer array (pointers to blocks for each slot)
    // +0x1010: start of linear pool of blocks (each 0xA0 bytes)

    // Allocate a new block from the pool using the current write index
    short writeIndex = *(short*)(this + 6);
    *(short*)(this + 4) = writeIndex;
    *(short*)(this + 6) = writeIndex + 1;

    // Compute block address: base = this + 0x1010 + writeIndex * 0xA0
    char* blockBase = (char*)this + 0x1010 + writeIndex * 0xA0;

    // Store pointer in the array for the given slot (bone index)
    *(int**)(this + 0x810 + slotIndex * 4) = (int*)blockBase;

    // Copy first 16 floats (64 bytes) from matrix1 to block offset 0x00
    int* dst = (int*)blockBase;
    const int* src1 = (const int*)matrix1;
    for (int i = 0; i < 16; i++)
        dst[i] = src1[i];

    // Copy second 16 floats (64 bytes) from matrix2 to block offset 0x40
    dst = (int*)(blockBase + 0x40);
    const int* src2 = (const int*)matrix2;
    for (int i = 0; i < 16; i++)
        dst[i] = src2[i];

    // Copy 4 floats (16 bytes) from vector1 to block offset 0x80
    dst = (int*)(blockBase + 0x80);
    const int* src3 = (const int*)vector1;
    dst[0] = src3[0];
    dst[1] = src3[1];
    dst[2] = src3[2];
    dst[3] = src3[3];

    // Copy 4 floats (16 bytes) from vector2 to block offset 0x90
    dst = (int*)(blockBase + 0x90);
    const int* src4 = (const int*)vector2;
    dst[0] = src4[0];
    dst[1] = src4[1];
    dst[2] = src4[2];
    dst[3] = src4[3];
}