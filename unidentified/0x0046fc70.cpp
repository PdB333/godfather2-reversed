// FUNC_ADDR: 0x0046fc70, Transform::translateByVector
void __thiscall Transform::translateByVector(float* translationVec) {
    // Copy the current 4x4 matrix (stored as 16 ints at offset 0x34) to local stack
    int localMatrix[16];
    int* src = &this->matrix[0]; // this->matrix starts at offset 0x34 in the object
    int* dst = localMatrix;
    for (int i = 0; i < 16; i++) {
        dst[i] = src[i];
    }

    // Add the translation vector to the existing translation (stored in row 3, indices 12-14)
    float* localTranslation = reinterpret_cast<float*>(&localMatrix[12]);
    localTranslation[0] += translationVec[0];
    localTranslation[1] += translationVec[1];
    localTranslation[2] += translationVec[2];

    // Copy the modified matrix back to the object
    for (int i = 0; i < 16; i++) {
        src[i] = dst[i];
    }

    // Set the fourth column to [0,0,0,1] (W components of rows 0-3)
    this->matrix[3]  = 0; // row0.w (offset 0x37)
    this->matrix[7]  = 0; // row1.w (offset 0x3b)
    this->matrix[11] = 0; // row2.w (offset 0x3f)
    this->matrix[15] = DAT_00e2b1a4; // row3.w (offset 0x43) – typically 1.0f

    // Call internal update/notification functions
    FUN_006101b0();
    (*(this->vtable + 0x68))(this);
}