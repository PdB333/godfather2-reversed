// FUNC_NAME: blendTransforms

// Function: 0x006103f0
// Role: Blends three transform arrays of 8 floats each (likely quaternion+translation or two 4-vectors)
// Calls internal blend function at 0x00610690

void blendTransforms(float* source1, float* source2, float* source3) {
    float blendBuffer1[8];
    float blendBuffer2[8];
    float blendBuffer3[8];

    // Copy first source (always present)
    blendBuffer1[0] = source1[0];
    blendBuffer1[1] = source1[1];
    blendBuffer1[2] = source1[2];
    blendBuffer1[3] = source1[3];
    blendBuffer1[4] = source1[4];
    blendBuffer1[5] = source1[5];
    blendBuffer1[6] = source1[6];
    blendBuffer1[7] = source1[7];

    // Copy second source (optional)
    float* ptr2 = nullptr;
    if (source2 != nullptr) {
        blendBuffer2[0] = source2[0];
        blendBuffer2[1] = source2[1];
        blendBuffer2[2] = source2[2];
        blendBuffer2[3] = source2[3];
        blendBuffer2[4] = source2[4];
        blendBuffer2[5] = source2[5];
        blendBuffer2[6] = source2[6];
        blendBuffer2[7] = source2[7];
        ptr2 = blendBuffer2;
    }

    // Copy third source (optional)
    float* ptr3 = nullptr;
    if (source3 != nullptr) {
        blendBuffer3[0] = source3[0];
        blendBuffer3[1] = source3[1];
        blendBuffer3[2] = source3[2];
        blendBuffer3[3] = source3[3];
        blendBuffer3[4] = source3[4];
        blendBuffer3[5] = source3[5];
        blendBuffer3[6] = source3[6];
        blendBuffer3[7] = source3[7];
        ptr3 = blendBuffer3;
    }

    // Call internal blend function
    FUN_00610690(blendBuffer1, ptr2, ptr3);
}