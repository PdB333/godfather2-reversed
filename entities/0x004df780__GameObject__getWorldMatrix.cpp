// FUNC_NAME: GameObject::getWorldMatrix

// Reconstructed copy of world matrix from object's transform data.
// If transform pointer is null, returns an identity matrix using a stored float constant.
void __thiscall GameObject::getWorldMatrix(GameObject* this, float outMatrix[16]) {
    // +0x00: pointer to transform data block
    TransformData* transform = this->transformPtr;

    if (transform != nullptr) {
        // +0x30: 16 floats forming the 4x4 world matrix
        __builtin_memcpy(outMatrix, &transform->matrix, sizeof(float) * 16);
    } else {
        // Use a global constant (likely 1.0f) for the diagonal
        float identityVal = *reinterpret_cast<float*>(&DAT_00e2b1a4);

        // Set identity matrix
        outMatrix[0]  = identityVal;
        outMatrix[1]  = 0.0f;
        outMatrix[2]  = 0.0f;
        outMatrix[3]  = 0.0f;
        outMatrix[4]  = 0.0f;
        outMatrix[5]  = identityVal;
        outMatrix[6]  = 0.0f;
        outMatrix[7]  = 0.0f;
        outMatrix[8]  = 0.0f;
        outMatrix[9]  = 0.0f;
        outMatrix[10] = identityVal;
        outMatrix[11] = 0.0f;
        outMatrix[12] = 0.0f;
        outMatrix[13] = 0.0f;
        outMatrix[14] = 0.0f;
        outMatrix[15] = identityVal;
    }
}