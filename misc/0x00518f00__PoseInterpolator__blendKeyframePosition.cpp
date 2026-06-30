// FUNC_NAME: PoseInterpolator::blendKeyframePosition
int __thiscall PoseInterpolator::blendKeyframePosition(float *inputScale, float blendWeight)
{
    // Global constant, likely 1.0f or animation max time
    float maxBlendWeight = DAT_00e2b1a4;
    float clampedBlend = blendWeight;

    // Clamp blendWeight to [0, maxBlendWeight]
    if (0.0f < blendWeight) {
        if (maxBlendWeight <= blendWeight) {
            clampedBlend = maxBlendWeight;
        }
    } else {
        clampedBlend = 0.0f;
    }

    // Number of keyframes (total frames) stored at offset 0x1C
    short numFrames = *(short *)((char *)this + 0x1C);

    // Compute absolute blend value in frame units
    float frameBlend = (float)(int)numFrames * clampedBlend;
    int baseFrame = (int)frameBlend;
    float mixFraction;

    // Determine frame index and fraction
    if (baseFrame < numFrames) {
        mixFraction = frameBlend - (float)baseFrame;
    } else {
        // Clamp to last frame
        baseFrame = numFrames - 1;
        mixFraction = maxBlendWeight; // Usually 1.0f
    }

    // Read the remapped keyframe index from the keyframe data at offset 0x3C
    // Each keyframe is 0x20 bytes, first element is a short (index)
    int keyIndexA = (int)*(short *)(baseFrame * 0x20 + 0x3C + (char *)this);
    int keyIndexB = keyIndexA - 1;
    if (keyIndexB < 0) {
        keyIndexB = 0;
    }

    // Pointers to the two keyframe vectors (positions) in the keyframe array
    float *keyframeA = (float *)(keyIndexB * 0x20 + (char *)this);
    float *keyframeB = (float *)(keyIndexA * 0x20 + (char *)this);

    // Scale the keyframe components by the input scale vector
    float scaledA_x = *keyframeA * *inputScale;
    float scaledA_y = keyframeA[1] * inputScale[1];
    float scaledA_z = keyframeA[2] * inputScale[2];

    // Second keyframe scaled components
    float scaledB_x = *keyframeB * *inputScale;
    float scaledB_y = keyframeB[1] * inputScale[1];
    float scaledB_z = keyframeB[2] * inputScale[2];

    // Output pointer (likely member or parameter stored in ESI)
    float *outputPose = /* ESI */; // assumed to be a class member or passed via register

    // Linear interpolation between the two scaled keyframes
    outputPose[0] = mixFraction * (scaledB_x - scaledA_x) + scaledA_x;
    outputPose[1] = mixFraction * (scaledB_y - scaledA_y) + scaledA_y;
    outputPose[2] = mixFraction * (scaledB_z - scaledA_z) + scaledA_z;

    // Set the fourth output component to the global constant (e.g., quaternion w)
    outputPose[3] = maxBlendWeight;

    // Call unknown processing function (likely performs quaternion normalization or additional math)
    unknownFunction();

    // Zero out the eighth output component (e.g., quaternion x, y, or z?)
    outputPose[7] = 0.0f;

    return 1; // Success
}