// FUNC_NAME: SimManager::constructPackedObject
void __thiscall SimManager::constructPackedObject(
    void *this,                   // ECX (unused, allocator is global)
    int *baseObject,             // param_1: pointer to 64-byte base structure
    int objectId,                // param_2
    int param3,                  // param_3
    int param4,                  // param_4
    float *extraData1,           // param_5: 16-byte data
    float *extraData2,           // param_6: 16-byte data
    int param7,                  // param_7
    double *matrixData           // in_EAX: 4 doubles (32 bytes)
)
{
    // Global allocator state (DAT_01206880 + 0x14)
    int *allocPtr = *(int **)(DAT_01206880 + 0x14);

    // Write vtable pointer for created object
    *(void ***)allocPtr = &PTR_LAB_01126d70;
    allocPtr += 4;

    // Write object ID
    *(int *)allocPtr = objectId;
    allocPtr += 4;

    // Align next allocation to 16-byte boundary
    void *dst = (void *)(((int)allocPtr + 0xf) & ~0xf);
    *(int **)(DAT_01206880 + 0x14) = (int *)dst; // update allocator position

    // Build the 0x90-byte object data on stack
    struct PackedData {
        int base[16];        // 64 bytes from baseObject
        float extra1[4];     // 16 bytes from extraData1
        float extra2[4];     // 16 bytes from extraData2
        double matrix[4];    // 32 bytes from matrixData
        int extraParam3;     // param_3
        int extraParam4;     // param_4
        int extraParam7;     // param_7
        // implicit padding to 0x90
    } packedData;

    // Fill the structure
    memcpy(packedData.base, baseObject, 64);
    memcpy(packedData.extra1, extraData1, 16);
    memcpy(packedData.extra2, extraData2, 16);
    memcpy(packedData.matrix, matrixData, 32);
    packedData.extraParam3 = param3;
    packedData.extraParam4 = param4;
    packedData.extraParam7 = param7;

    // Copy entire packed data to aligned buffer
    memcpy(dst, &packedData, 0x90);

    // Advance allocator past the copied data
    *(int **)(DAT_01206880 + 0x14) = (int *)((int)dst + 0x90);
}