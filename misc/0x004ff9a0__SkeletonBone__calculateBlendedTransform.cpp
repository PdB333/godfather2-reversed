// FUNC_NAME: SkeletonBone::calculateBlendedTransform
void __thiscall SkeletonBone::calculateBlendedTransform(SkeletonBone *this)
{
    float *translationSrc;
    uint tlsIndex;
    float *outputTranslation;
    SkeletonBoneData *boneData;
    float rotScale[12]; // 3x4 rotation/scale part
    float translation[4]; // translation row

    // Early exit if no output buffer
    if (this->m_pOutputMatrixBlock == 0) {
        return;
    }

    // Get per-thread bone index from TLS (likely a global animation stack)
    tlsIndex = *(uint *)(*(int **)__readfsdword(0x2c) + 8);
    boneData = this->m_pBoneData;
    // Source matrix is stored as 16 floats: rotation/scale at +0x50, translation at +0x80
    translationSrc = (float *)(this->m_pSourceMatrix + 0x80 + tlsIndex);
    // Load translation from source (4 floats)
    translation[0] = translationSrc[0];
    translation[1] = translationSrc[1];
    translation[2] = translationSrc[2];
    translation[3] = translationSrc[3];

    tlsIndex = *(uint *)(*(int **)__readfsdword(0x2c) + 8); // actually same offset, but the assignment is needed
    // After first use, tlsIndex is reused as an offset into the source matrix block
    // Actually the code reassigns iVar5 to base + iVar5, so we reconstruct:
    int matrixBaseOffset = this->m_pSourceMatrix + (*(int *)(*(int **)__readfsdword(0x2c) + 8));
    // Note: The original code used the same tlsIndex value twice; we keep it as offset.

    // If bone data flags don't have bit 1 or 2 set (0x6), add local translation offset
    if ((boneData->flags & 6) == 0) {
        translation[0] += boneData->localOffsetX;
        translation[1] += boneData->localOffsetY;
        translation[2] += boneData->localOffsetZ;
    }

    // If blend mode is 0, just set the translation on the output object (call into another function)
    if (boneData->blendMode == 0) {
        FUN_004e9440(this->m_pOutputMatrixBlock, translation);
        return;
    }

    // Otherwise, build full 4x4 matrix
    // Check if matrix needs to be computed from scratch (flag 0x2000)
    if ((boneData->flags & 0x2000) == 0) {
        // Copy rotation/scale part (12 floats) from source matrix at offset +0x50
        memcpy(rotScale, (void *)(matrixBaseOffset + 0x50), sizeof(rotScale));
    } else {
        // Alternative: compute identity or from some other function
        FUN_004fef50();
    }

    // Write the full matrix (16 floats) into output buffer, indexed by TLS bone index
    if (this->m_pOutputMatrixBlock != 0) {
        float *outputDest = (float *)(*(int *)(this->m_pOutputMatrixBlock + 0x18) +
                                      (*(int *)(*(int **)__readfsdword(0x2c) + 8)));
        // Copy rotation/scale (12 floats)
        memcpy(outputDest, rotScale, sizeof(rotScale));
        // Copy translation (4 floats)
        memcpy(outputDest + 12, translation, sizeof(translation));
    }
}