// FUNC_NAME: scaleMatrixArray
// Copies three 4x4 matrices (offset 0x50, 0x90, 0xd0) from source struct to destination struct, scaling each component by factor.
// Called by FUN_00823470.
int __cdecl scaleMatrixArray(int destStruct, int srcStruct, float scale)
{
    float *destRowIter = (float *)(destStruct + 0x50);
    float *srcRowIter = (float *)(srcStruct + 0xd0);
    int rowsRemaining = 4;

    // Internal initialization (possibly matrix identity or reset)
    initializeSomething();

    do {
        // Source rows are derived from offset difference and advancing dest pointer
        float *srcRow0 = (float *)((srcStruct - destStruct) + (int)destRowIter); // == srcStruct + 0x50 + offset
        // Copy first matrix row (at src+0x50 + rowOffset)
        *destRowIter         = scale * srcRow0[0];
        destRowIter[1]       = scale * srcRow0[1];
        destRowIter[2]       = scale * srcRow0[2];
        destRowIter[3]       = scale * srcRow0[3];

        // Copy second matrix row (at src+0x90 + rowOffset)
        float *srcRow1 = srcRowIter - 0x10; // relative to srcRowIter (start = src+0xd0)
        destRowIter[0x10]     = scale * srcRow1[0];
        destRowIter[0x11]     = scale * srcRow1[1];
        destRowIter[0x12]     = scale * srcRow1[2];
        destRowIter[0x13]     = scale * srcRow1[3];

        // Copy third matrix row (at src+0xd0 + rowOffset)
        destRowIter[0x20]     = scale * srcRowIter[0];
        destRowIter[0x21]     = scale * srcRowIter[1];
        destRowIter[0x22]     = scale * srcRowIter[2];
        destRowIter[0x23]     = scale * srcRowIter[3];

        destRowIter += 4;  // move to next row (16 bytes)
        srcRowIter += 4;
        rowsRemaining--;
    } while (rowsRemaining != 0);

    return destStruct;
}