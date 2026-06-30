// FUNC_NAME: AnimationController::blendBoneTransform
// 0x00511800
void AnimationController::blendBoneTransform(float blendWeight, int boneIndex) {
    unsigned int renderContext = *(unsigned int*)(*(int*)(this + 0x50) + 0x90);
    int* targetBoneData = *(int**)(this + 0x58);

    if (targetBoneData != nullptr && (*(byte*)(*(int*)(this + 0x10) + 0x104) & 1) != 0) {
        // Read source transforms from register-allocated pointer (passed via ESI)
        double posQ = *(double*)(sourceTransform + 0xc);    // likely position/quaternion at +0xc and +0xe
        float extra = sourceTransform[0xe];
        *(unsigned int*)(targetBoneData + 0x94) &= 0xfffffff7; // clear bit 3 (0x8)
        *(double*)(targetBoneData + 0x80) = posQ;
        *(unsigned long long*)(targetBoneData + 0x88) = CONCAT44(blendWeight, extra);
        FUN_0044f770(targetBoneData, 0);
    }

    // Scale and copy transform matrix (16 floats)
    float dstMatrix[16];
    dstMatrix[0] = sourceTransform[0] * blendWeight;
    dstMatrix[1] = sourceTransform[1] * blendWeight;
    dstMatrix[2] = sourceTransform[2] * blendWeight;
    dstMatrix[3] = sourceTransform[3] * blendWeight;
    dstMatrix[4] = sourceTransform[4] * blendWeight;
    dstMatrix[5] = sourceTransform[5] * blendWeight;
    dstMatrix[6] = sourceTransform[6] * blendWeight;
    dstMatrix[7] = sourceTransform[7] * blendWeight;
    dstMatrix[8] = sourceTransform[8] * blendWeight;
    dstMatrix[9] = sourceTransform[9] * blendWeight;
    dstMatrix[10] = sourceTransform[10] * blendWeight;
    dstMatrix[11] = sourceTransform[0xb] * blendWeight;
    dstMatrix[12] = sourceTransform[0xc]; // last four remain unscaled
    dstMatrix[13] = sourceTransform[0xd];
    dstMatrix[14] = sourceTransform[0xe];
    dstMatrix[15] = sourceTransform[0xf];

    FUN_00433950(boneIndex); // likely validates bone index
    unsigned int flags = (~(*(unsigned int*)(*(int*)(this + 0x10) + 0x108) >> 0x1a) & 4) | 2;
    FUN_00433700(renderContext, &dstMatrix, 0, sourceTransform[0x10], flags, 0);
}