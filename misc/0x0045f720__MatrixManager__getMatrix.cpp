// FUNC_NAME: MatrixManager::getMatrix
void __thiscall MatrixManager::getMatrix(float outMatrix[16], uint32_t* flags, bool applyTransform)
{
    // Check if internal matrix provider (param_1 + 0x218) is null
    if (*(int*)(this + 0x218) == 0) {
        // Fallback to default matrix computation
        FUN_00471590(outMatrix, flags, applyTransform);
        return;
    }

    float localMatrix[16];
    if ((*flags & 2) == 0) {
        // Bit 1 not set
        if ((*flags & 1) == 0) {
            // Bit 0 not set: call with the provider pointer
            FUN_00577b30(*(int*)(this + 0x218));
        } else {
            // Bit 0 set: call static helper
            FUN_00577f40();
        }
        // Initialize a temporary matrix: translation + scale? (position = 0,0,0, scale = DAT_00e2b1a4)
        localMatrix[0] = 0.0f; // local_44
        localMatrix[1] = 0.0f; // local_34
        localMatrix[2] = 0.0f; // local_24
        localMatrix[3] = DAT_00e2b1a4; // +0x14
        FUN_00417560(localMatrix); // Build the matrix from the parameters
        float* src = localMatrix;
    } else {
        // Bit 1 set: use pre-stored matrix at offset 0xD0
        float* src = (float*)(this + 0xD0);
    }

    // Copy 16 floats (4x4 matrix) from src to output
    for (int i = 0; i < 16; i++) {
        outMatrix[i] = src[i];
    }

    // If applyTransform is non-zero, apply an in-place transformation (e.g., transpose or invert)
    if ((char)applyTransform != 0) {
        FUN_0043a2a0(outMatrix, outMatrix);
    }
}