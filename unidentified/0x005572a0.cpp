// FUN_005572a0: EARSObject::initTransformFromTarget
void __fastcall EARSObject::initTransformFromTarget(int *this_, void *targetMatrix) {
    struct AlignedData {
        float w;           // +0x00 (uStack_54)
        void *buffer;      // +0x04 (puStack_5c)
        int zero1;         // +0x08 (local_44)
        int zero2;         // +0x0C (local_34)
        float outX;        // +0x10 (uStack_2c)
        float outY;        // +0x14 (uStack_28)
        float outZ;        // +0x18 (local_24)
        float wConst;      // +0x1C (local_14)
        void *savedParam;  // +0x20 (uStack_58)
    } localData;

    localData.buffer = localData; // actually puStack_5c points to another local array (not shown in struct)
    localData.w = 1.0f;
    localData.zero1 = 0;
    localData.zero2 = 0;
    localData.outZ = 0.0f;
    localData.wConst = DAT_00e2b1a4; // global constant (likely 0.0f or identity quaternion w)
    localData.savedParam = targetMatrix;

    // Call virtual function at index 0x90 (typically getTransform or getWorldMatrix)
    // This function writes into localData.outX, outY, outZ (and possibly other fields)
    (*(void (**)(void*, void*))(*(int*)this_ + 0x90))(this_, targetMatrix);

    // Copy result to this_'s orientation quaternion at offset 0x30
    *(float *)((int)this_ + 0x30) = localData.outX;   // +0x30
    *(float *)((int)this_ + 0x34) = localData.outY;   // +0x34
    *(float *)((int)this_ + 0x38) = localData.outZ;   // +0x38
    *(float *)((int)this_ + 0x3C) = DAT_00e2b1a4;     // +0x3C, constant w component

    // Finalize initialization with the local buffer
    FUN_004b59d0(&localData.buffer);
}