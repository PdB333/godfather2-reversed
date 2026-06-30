// FUNC_NAME: EARSNode::getWorldTransformMatrix
// 0x0043ac60
// Returns a 4x4 transformation matrix (16 floats) into outMatrix based on object type.
// If object type (at +6) is not 0x25e3, matrix is stored inline at +8.
// If type is 0x25e3, the matrix is obtained via indirect pointer: *(int*)(this+0) + *(int*)(this+8)
// If that pointer is null, returns an identity matrix scaled by g_identityScale (0x00e2b1a4).

void __thiscall EARSNode::getWorldTransformMatrix(EARSNode* this, float* outMatrix) {
    // Known global: identity scale factor (likely 1.0f)
    float identityScale = *(float*)0x00e2b1a4;

    // Object type identifier at offset +6 (2 bytes)
    if (*(short*)((unsigned char*)this + 6) != 0x25e3) {
        // Type A: matrix stored directly at this+8
        // Copy 16 floats (64 bytes) from this+8 to output
        float* src = (float*)((unsigned char*)this + 8);
        for (int i = 0; i < 16; i++) {
            outMatrix[i] = src[i];
        }
        return;
    }

    // Type B: matrix via pointer
    int* indirectBase = *(int**)this;          // offset +0: pointer base
    int* offsetAddition = *(int**)((unsigned char*)this + 8); // offset +8: offset addition

    if (indirectBase != nullptr) {
        // Matrix location = base + offset
        float* src = (float*)((unsigned char*)indirectBase + (int)offsetAddition);
        for (int i = 0; i < 16; i++) {
            outMatrix[i] = src[i];
        }
        return;
    }

    // Default: identity matrix scaled by identityScale (diagonal entries at indices 0,5,10,15)
    outMatrix[0]  = identityScale;
    outMatrix[1]  = 0.0f;
    outMatrix[2]  = 0.0f;
    outMatrix[3]  = 0.0f;
    outMatrix[4]  = 0.0f;
    outMatrix[5]  = identityScale;
    outMatrix[6]  = 0.0f;
    outMatrix[7]  = 0.0f;
    outMatrix[8]  = 0.0f;
    outMatrix[9]  = 0.0f;
    outMatrix[10] = identityScale;
    outMatrix[11] = 0.0f;
    outMatrix[12] = 0.0f;
    outMatrix[13] = 0.0f;
    outMatrix[14] = 0.0f;
    outMatrix[15] = identityScale;
}