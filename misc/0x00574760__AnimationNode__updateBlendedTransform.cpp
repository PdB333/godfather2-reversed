// FUNC_NAME: AnimationNode::updateBlendedTransform
void AnimationNode::updateBlendedTransform(BlendOutput* outTransform)
{
    float* blendFactor = this->mBlendFactor; // this+0x8
    if (blendFactor == nullptr) {
        return;
    }

    float* srcData = this->mSourceData; // this+0x0, points to a quaternion+position
    float rotation[4];
    float translation[4];

    // Handle rotation interpolation (quaternion)
    if ((this->mFlags & 4) == 0) {
        // No interpolation: copy directly from source
        rotation[0] = srcData[0];
        rotation[1] = srcData[1];
        rotation[2] = srcData[2];
        rotation[3] = srcData[3];
    } else {
        // Interpolate quaternion using slerp
        float t = *blendFactor;
        float* targetContext = (float*)this->mTargetContext; // this+0x4
        quaternionSlerp(t, srcData, targetContext, rotation, DAT_00e2e780);
    }

    // Handle translation interpolation
    if ((this->mFlags & 8) == 0) {
        // No interpolation: copy from source
        translation[0] = srcData[4];
        translation[1] = srcData[5];
        translation[2] = srcData[6];
        translation[3] = srcData[7];
    } else {
        // Linear interpolation between source and target
        float t = *blendFactor;
        float* targetPos = (float*)this->mTargetContext; // target also contains position at +0x10, +0x14, +0x18
        translation[0] = (targetPos[4] - srcData[4]) * t + srcData[4];
        translation[1] = (targetPos[5] - srcData[5]) * t + srcData[5];
        translation[2] = (targetPos[6] - srcData[6]) * t + srcData[6];
    }

    // Apply rotation to output transform (e.g., convert quaternion to matrix)
    applyRotationToTransform(rotation, outTransform);

    // Write translation into the output struct at offsets +0x30, +0x34, +0x38, +0x3c
    outTransform->positionX = translation[0];
    outTransform->positionY = translation[1];
    outTransform->positionZ = translation[2];
    // The w component is forced to a constant (homogeneous coordinate)
    outTransform->positionW = DAT_00e2b1a4;

    // Cleanup or unlock (likely release of temporary data)
    releaseInterpolationData();
}