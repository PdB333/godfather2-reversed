// FUNC_NAME: CharacterRenderer::updateSkinningMatrices
// Function at 0x0041c460: Copies two 4x4 matrices (128 bytes) from source object to global skinning arrays.
// Conditional on a flag at this+0x0c (if zero, copy is performed).
// Matrices are stored in global arrays: gSkinningMatrix0[16] (0x01163610) and gSkinningMatrix1[16] (0x011629d0).

void CharacterRenderer::updateSkinningMatrices(int* source) {
    // +0x0c : bool isDirty or skip flag? If zero, continue.
    if (*(char*)(this + 0x0c) == 0) {
        // Copy first 4x4 matrix from source +0x40 to global array 0
        for (int i = 0; i < 16; i++) {
            gSkinningMatrix0[i] = *(int*)(source + 0x40 + i * 4);
        }
        // Copy second 4x4 matrix from source +0x80 to global array 1
        for (int i = 0; i < 16; i++) {
            gSkinningMatrix1[i] = *(int*)(source + 0x80 + i * 4);
        }
    }
    // else skip update
}