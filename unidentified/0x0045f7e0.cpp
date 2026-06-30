// FUN_NAME: TransformHelper::getTransform
void __thiscall TransformHelper::getTransform(void* this, Matrix4x4* outMatrix, uint* flags, char applyPostProcess) {
    // +0x218: pointer to a data source (skeleton, animation, etc.)
    int* dataSource = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x218);
    float identityVal = *reinterpret_cast<float*>(0x00e2b1a4); // global identity constant (likely 1.0f)

    if (dataSource == nullptr || (*flags & 2) != 0) {
        // Set matrix to identity (diagonal = global constant, off-diagonal = 0)
        outMatrix->m00 = identityVal;
        outMatrix->m01 = 0.0f;
        outMatrix->m02 = 0.0f;
        outMatrix->m03 = 0.0f;
        outMatrix->m10 = 0.0f;
        outMatrix->m11 = identityVal;
        outMatrix->m12 = 0.0f;
        outMatrix->m13 = 0.0f;
        outMatrix->m20 = 0.0f;
        outMatrix->m21 = 0.0f;
        outMatrix->m22 = identityVal;
        outMatrix->m23 = 0.0f;
        outMatrix->m30 = 0.0f;
        outMatrix->m31 = 0.0f;
        outMatrix->m32 = 0.0f;
        outMatrix->m33 = identityVal;
    } else {
        if ((*flags & 1) == 0) {
            // Compute transform using the data source
            FUN_00577b30(dataSource);
        } else {
            // Alternate transform computation
            FUN_00577f40();
        }
        if (applyPostProcess != '\0') {
            // Apply post-processing to the output matrix (e.g., normalization)
            FUN_0043a2a0(outMatrix, outMatrix);
        }
    }
}