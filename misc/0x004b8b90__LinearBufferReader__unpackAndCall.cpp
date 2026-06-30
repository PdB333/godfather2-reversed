// FUNC_NAME: LinearBufferReader::unpackAndCall
// Function at 0x004b8b90: Reads a packed argument block from a linear buffer and calls a function pointer with the extracted arguments.
// The buffer is pointed by this+0x18. After consuming data, the pointer is updated.
void __thiscall LinearBufferReader::unpackAndCall(void* this, uint32_t** ppFunc) {
    // Read first 5 dwords from the buffer: 3 arbitrary arguments, then first level count and element size.
    uint32_t* currentPtr = *(uint32_t**)((char*)this + 0x18);          // +0x18: current buffer read pointer

    uint32_t arg0 = *currentPtr;        // first argument (uVar3)
    currentPtr++;
    uint32_t arg1 = *currentPtr;        // second argument (uVar4)
    currentPtr++;
    uint32_t arg2 = *currentPtr;        // third argument (uVar5)
    currentPtr++;
    int array1Count = *currentPtr;      // iVar6: number of elements in first array
    currentPtr++;
    int array1ElemSize = *currentPtr;   // iVar7: element size (must be power of 2 for alignment)
    currentPtr++;

    // Align the pointer after the header + array1ElemSize + 0x13 to the element size boundary.
    // This likely jumps over a variable-length header or padding.
    uint32_t aligned1 = ((uint32_t)currentPtr + array1ElemSize + 0x13) & ~(array1ElemSize - 1U);
    // Compute pointer to first array (elements of 4 bytes each)
    int* array1Ptr = (int*)(array1Count * 4 + aligned1);
    *(uint32_t**)((char*)this + 0x18) = (uint32_t*)array1Ptr;   // update buffer pointer

    // Read second level count and size from the beginning of first array.
    int array2Count = *array1Ptr;            // iVar8
    int array2ElemSize = *(array1Ptr + 1);   // iVar9

    // Align after reading these two ints, adding array2ElemSize + 7 then align to array2ElemSize.
    uint32_t aligned2 = ((uint32_t)array1Ptr + array2ElemSize + 7) & ~(array2ElemSize - 1U);
    // Compute pointer to second array (elements of 0xc = 12 bytes each)
    int* array2Ptr = (int*)(array2Count * 0xc + aligned2);
    *(uint32_t**)((char*)this + 0x18) = (uint32_t*)array2Ptr;

    // Read third level count and size from the beginning of second array.
    int array3Count = *array2Ptr;            // iVar10
    int array3ElemSize = *(array2Ptr + 1);    // iVar11

    // Align after these two ints, adding array3ElemSize + 7 then align to array3ElemSize.
    uint32_t aligned3 = ((uint32_t)array2Ptr + array3ElemSize + 7) & ~(array3ElemSize - 1U);
    // Compute pointer to third array (elements of 8 bytes each)
    uint16_t* array3Ptr = (uint16_t*)(array3Count * 8 + aligned3);
    *(uint32_t**)((char*)this + 0x18) = (uint32_t*)array3Ptr;

    // Read first 2-byte value from the third array.
    uint16_t firstValue = *array3Ptr;

    // Update buffer pointer to the next aligned position (skip 5 bytes and align to 4)
    *(uint32_t*)((char*)this + 0x18) = ((uint32_t)array3Ptr + 5U) & 0xFFFFFFFC;

    // Build 64-bit pointers with upper 32 bits set to -1 if count is non-zero (likely null-terminated or validity flag)
    uint64_t ptr1 = (array1Count != 0) ? (0xFFFFFFFF00000000ULL | aligned1) : (0x0000000000000000ULL | aligned1);
    uint64_t ptr2 = (array2Count != 0) ? (0xFFFFFFFF00000000ULL | aligned2) : (0x0000000000000000ULL | aligned2);
    uint64_t ptr3 = (array3Count != 0) ? (0xFFFFFFFF00000000ULL | aligned3) : (0x0000000000000000ULL | aligned3);

    // Call the function pointed by *ppFunc with the extracted arguments.
    // The function signature is unknown; arguments are passed as 32-bit chunks.
    // The mapping is: arg0, arg1, arg2, [lower32(ptr1), upper32(ptr1)], array1ElemSize,
    //                 [lower32(ptr2), upper32(ptr2)], array2ElemSize,
    //                 [lower32(ptr3), upper32(ptr3)], array3ElemSize,
    //                 firstValue
    typedef void (*FuncType)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint16_t);
    FuncType func = (FuncType)(*ppFunc);
    func(arg0, arg1, arg2, 
         (uint32_t)(ptr1 & 0xFFFFFFFF), (uint32_t)(ptr1 >> 32), array1ElemSize,
         (uint32_t)(ptr2 & 0xFFFFFFFF), (uint32_t)(ptr2 >> 32), array2ElemSize,
         (uint32_t)(ptr3 & 0xFFFFFFFF), (uint32_t)(ptr3 >> 32), array3ElemSize,
         firstValue);
}