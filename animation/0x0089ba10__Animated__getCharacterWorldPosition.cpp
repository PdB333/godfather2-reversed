// FUNC_NAME: Animated::getCharacterWorldPosition

void __thiscall Animated::getCharacterWorldPosition(Animated *this, float outWorldPos[4]) {
    // Check if this object has a valid type and is not a special node (type 0x48)
    if (this->type != 0 && this->type != 0x48) {
        // Get three bone matrix pointers (likely from left hand, right hand, etc.)
        float *matrix1 = (float *)getBoneMatrix();  // +0x30 = translation.x
        float *matrix2 = (float *)getBoneMatrix();  // +0x34 = translation.y
        float *matrix3 = (float *)getBoneMatrix();  // +0x38 = translation.z

        // Combine components into a 4-element vector (position + w)
        outWorldPos[0] = matrix3[0x30 / 4];  // x from third bone
        outWorldPos[1] = matrix2[0x34 / 4];  // y from second bone
        outWorldPos[2] = matrix1[0x38 / 4];  // z from first bone
        outWorldPos[3] = g_constantW;  // global w component
    }
}