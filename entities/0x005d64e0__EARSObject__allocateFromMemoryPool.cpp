// FUNC_NAME: EARSObject::allocateFromMemoryPool
void __thiscall EARSObject::allocateFromMemoryPool(
    undefined4 *sourcePart1,             // +0x00 to +0x3F (16 dwords)
    int poolId,                          // written as second word after vtable
    undefined4 param3,                   // stored at struct offset +0x84 (+132)
    undefined4 param4,                   // stored at struct offset +0x88 (+136)
    undefined4 *sourcePart2,             // +0x40 to +0x4F (4 dwords)
    undefined4 *sourcePart3,             // +0x50 to +0x5F (4 dwords)
    undefined4 param7)                   // stored at struct offset +0x8C (+140)
{
    // Temporary struct combining all input data (144 bytes = 0x90)
    // Layout corresponds to the object being constructed
    struct ObjectData {
        // 16 dwords from sourcePart1 (offset 0x00-0x3F)
        undefined4 field_00[16];

        // 4 dwords from sourcePart2 (offset 0x40-0x4F)
        undefined4 field_40[4];

        // 4 dwords from sourcePart3 (offset 0x50-0x5F)
        undefined4 field_50[4];

        // Padding? (offset 0x60-0x63) - 4 bytes alignment before the 8-byte fields
        undefined4 padding;

        // 4 qwords from in_EAX (offset 0x64-0x83)
        undefined8 field_64[4];

        // Extra parameters (offset 0x84-0x8F)
        undefined4 field_84; // param3
        undefined4 field_88; // param4
        undefined4 field_8C; // param7
    };

    // Build temporary data on stack
    ObjectData tempData;

    // Copy from sourcePart1 (first 16 dwords)
    tempData.field_00[0]  = sourcePart1[0];
    tempData.field_00[1]  = sourcePart1[1];
    tempData.field_00[2]  = sourcePart1[2];
    tempData.field_00[3]  = sourcePart1[3];
    tempData.field_00[4]  = sourcePart1[4];
    tempData.field_00[5]  = sourcePart1[5];
    tempData.field_00[6]  = sourcePart1[6];
    tempData.field_00[7]  = sourcePart1[7];
    tempData.field_00[8]  = sourcePart1[8];
    tempData.field_00[9]  = sourcePart1[9];
    tempData.field_00[10] = sourcePart1[10];
    tempData.field_00[11] = sourcePart1[11];
    tempData.field_00[12] = sourcePart1[12];
    tempData.field_00[13] = sourcePart1[13];
    tempData.field_00[14] = sourcePart1[14];
    tempData.field_00[15] = sourcePart1[15];

    // Copy from sourcePart2 (next 4 dwords)
    tempData.field_40[0] = sourcePart2[0];
    tempData.field_40[1] = sourcePart2[1];
    tempData.field_40[2] = sourcePart2[2];
    tempData.field_40[3] = sourcePart2[3];

    // Copy from sourcePart3 (next 4 dwords)
    tempData.field_50[0] = sourcePart3[0];
    tempData.field_50[1] = sourcePart3[1];
    tempData.field_50[2] = sourcePart3[2];
    tempData.field_50[3] = sourcePart3[3];

    // Copy 4 qwords from in_EAX (pointer returned by previous call)
    tempData.field_64[0] = *in_EAX;
    tempData.field_64[1] = in_EAX[1];
    tempData.field_64[2] = in_EAX[2];
    tempData.field_64[3] = in_EAX[3];

    // Store extra parameters
    tempData.field_84 = param3;
    tempData.field_88 = param4;
    tempData.field_8C = param7;

    // Access the memory pool stack pointer (DAT_01206880 + 0x14)
    // The pool stores a vtable pointer and an ID, then the actual object data follows
    void **poolStack = (void**)(DAT_01206880 + 0x14);
    // Write vtable pointer
    *poolStack = (void*)&PTR_LAB_01126d70;  // VTable for this object type
    poolStack++;  // advance to next slot

    // Write the pool ID (param2)
    *poolStack = (void*)poolId;
    poolStack++;

    // Align next allocation to 16-byte boundary
    void *alignedDest = (void*)(((int)poolStack + 0xF) & 0xFFFFFFF0);
    *poolStack = alignedDest;  // update the pool stack pointer to after alignment? Actually the code shows: _Dst = (void *)(*piVar1 + 0xfU & 0xfffffff0); *piVar1 = (int)_Dst; So it updates the pool pointer to the aligned destination, then copies the data to that location.
    // Equivalent: the pool pointer becomes the address after the copy, but here we set it to alignedDest.

    // Copy the temporary object data into the aligned memory
    _memcpy(alignedDest, &tempData, sizeof(ObjectData));

    // Update pool stack pointer to after the copied data
    *poolStack = (char*)alignedDest + sizeof(ObjectData);
}