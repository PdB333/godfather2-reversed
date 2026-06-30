// FUNC_NAME: Node::getScaledWorldPosition
void __thiscall Node::getScaledWorldPosition(void* this, float* outVec) {
    // Get inner node pointer from this+0x2e8
    void* innerNode = *(void**)((char*)this + 0x2e8);

    // Get the world matrix from innerNode+0x18
    float* worldMatrix = *(float**)((char*)innerNode + 0x18);

    // Copy the 16 matrix elements into local array
    float matrixCopy[16];
    for (int i = 0; i < 16; ++i) {
        matrixCopy[i] = worldMatrix[i];
    }

    // Get the transformation function pointer from innerNode+0x10 vtable
    void** funcTable = *(void***)((char*)innerNode + 0x10);
    // +0x1c (28 bytes) -> function at index 7 (4-byte steps)
    typedef void (*TransformFunc)(const float*, float, float*);
    TransformFunc transformFunc = (TransformFunc)funcTable[7];

    // Output buffer (stack) – the function writes here
    float output[16];
    transformFunc(matrixCopy, DAT_00e3ac58, output);

    // Scale factor from global
    float scale = DAT_00e2cd54;

    // Extract translation-related components (original matrix at indices 13,14,7)
    // and blend with output values (from output[1], [2], [3])
    float origY = matrixCopy[13];  // original matrix row3 col1? (likely translation Y)
    float origZ = matrixCopy[14];  // original matrix row3 col2? (likely translation Z)
    float origW = matrixCopy[7];   // original matrix row1 col3? (likely something else)

    // Compute output vector components
    float outX = (output[1] + origY) * scale;
    float outY = (output[2] + origZ) * scale;
    // fStack_74 corresponds to output[3] (the fourth element of output)
    float outZ = (origW + output[3]) * scale;

    outVec[0] = outX;
    outVec[1] = outY;
    outVec[2] = outZ;
}