// FUN_00545640: Animated::getBoneWorldMatrix
void __thiscall Animated::getBoneWorldMatrix(void *this, int boneIndex, float *outMatrix) {
    // local_50 buffer used by virtual call (likely BoneTransform struct, 76 bytes)
    char boneTransformBuffer[76];
    // Local matrix storage (16 floats = 64 bytes), initialized to identity later
    float matrix[16];
    int i;

    // VTable call at offset 0x254: assume it's getBoneTransform(boneIndex, &boneTransformBuffer)
    (*(void (__thiscall **)(void *, int, char *))(*(int *)this + 0x254))(this, boneIndex, boneTransformBuffer);

    // Initialize matrix to identity (FUN_00aa1a10 likely sets identity)
    MatrixIdentity(matrix);

    // Copy elements from identity matrix to output (this is actually redundant after full copy below)
    outMatrix[0] = matrix[0];
    outMatrix[1] = matrix[1];
    outMatrix[2] = matrix[2];
    outMatrix[3] = 0.0f;                       // auStack_98[3] = 0
    outMatrix[4] = matrix[4];
    outMatrix[5] = matrix[5];                  // uStack_84
    outMatrix[6] = matrix[6];                  // uStack_80
    outMatrix[7] = 0.0f;                       // uStack_7c = 0
    outMatrix[8] = matrix[8];                  // uStack_78
    outMatrix[9] = matrix[9];                  // uStack_74
    outMatrix[10] = matrix[10];                // uStack_70
    outMatrix[11] = 0.0f;                      // uStack_6c = 0
    outMatrix[12] = matrix[12];                // uStack_68
    outMatrix[13] = matrix[13];                // uStack_64
    outMatrix[14] = matrix[14];                // uStack_60
    outMatrix[15] = 1.0f;                      // uStack_5c = 1.0f (DAT_00e2b1a4)

    // Unknown engine function (possibly matrix transpose or other operation)
    FUN_00417560();

    // Bulk copy 16 floats from local matrix to output (overwrites partial copy above)
    for (i = 0; i < 16; i++) {
        outMatrix[i] = matrix[i];
    }
}