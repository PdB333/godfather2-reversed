// FUNC_NAME: AnimationBlendTree::sampleBlend
// Address: 0x00595610
// Role: Samples an animation blend tree node at a given time, supporting different interpolation modes (1D, 2D, 3D, and Hermite cubic curves).
// Returns: 1 if single frame (no blending needed), 0 if interpolation was performed.

float AnimationBlendTree::sampleBlend(AnimationBlendNode* this, float time, float* outResult) {
    ushort numFrames = *(ushort*)((int)this + 6); // +0x06: keyframe count
    if (numFrames == 0) {
        *outResult = 0.0f;
        return 1.0f;
    }
    short blendType = *(short*)((float*)this + 2); // +0x02: blend mode (0=1D, 1=2D, 2=3D, 3=Hermite cubic)
    float* keyframes = this[3]; // +0x0C: pointer to keyframe data array
    // 1D blend (linear interpolation)
    if (blendType == 0) {
        if (numFrames == 1) {
            *outResult = *(float*)((int)keyframes + 4);
            return (float)numFrames;
        }
        float firstValue = keyframes[0]; // time value
        if (*(ushort*)((float*)this + 1) == numFrames) { // check if at last frame
            *outResult = *(float*)((int)firstValue + -4 + (uint)numFrames * 8);
            return 1.0f;
        }
        uint currentIndex = (uint)*(ushort*)((float*)this + 1); // +0x04: current keyframe index
        float minTime = *(float*)((int)firstValue + -8 + currentIndex * 8);
        int basePtr = (int)firstValue + currentIndex * 8;
        float maxTime = *(float*)((int)firstValue + currentIndex * 8);
        float t = (time - minTime) / (maxTime - minTime);
        // Clamp t (possibly via assertion)
        if ((t < 0.0f) || (1.0f < t)) {
            (**(code**)(*DAT_01205590 + 4))(); // error handler
        }
        float valueA = *(float*)(basePtr + -4);
        float valueB = *(float*)(basePtr + 4);
        *outResult = (valueB - valueA) * t + valueA;
        return 0.0f;
    }
    // 3D blend (Hermite cubic spline interpolation)
    if (blendType == 3) {
        if (numFrames == 1) {
            *outResult = *(float*)((int)keyframes + 0x14);
            return (float)numFrames;
        }
        if (*(ushort*)((float*)this + 1) == numFrames) {
            *outResult = *(float*)((int)keyframes + -4 + (uint)numFrames * 0x18);
            return 1.0f;
        }
        uint currentIdx = (uint)*(ushort*)((float*)this + 1);
        float* frameArray = (float*)((int)this[3]); // keyframes
        float minT = *(float*)((int)frameArray + -0x18 + currentIdx * 0x18);
        float* segmentBase = (float*)((int)frameArray + currentIdx * 0x18);
        float maxT = *segmentBase;
        float t = (time - minT) / (maxT - minT);
        if ((*(ushort*)((float*)this + 1) != numFrames) && (t < 0.0f)) {
            (**(code**)(*DAT_01205590 + 4))(); // error handler
        }
        float p0 = segmentBase[-4]; // position at t=0
        // Hermite basis functions (simplified from decompiled constants)
        float m0 = segmentBase[-1]; // tangent at start
        float m1 = segmentBase[5];  // tangent at end
        float p1 = segmentBase[1];  // position at t=1
        // Hermite interpolation: p(t) = (2t^3 - 3t^2 + 1)*p0 + (t^3 - 2t^2 + t)*m0 + (-2t^3 + 3t^2)*p1 + (t^3 - t^2)*m1
        // Approximate using decompiled constants (assumed Hermite basis coefficients)
        float t2 = t * t;
        float t3 = t2 * t;
        *outResult = (p0 * 2.0f - p1 * 2.0f + m0 + m1) * t3 + 
                     (-3.0f * p0 + 3.0f * p1 - 2.0f * m0 - m1) * t2 + 
                     m0 * t + p0;
        return 0.0f;
    }
    // 2D blend (quadratic bezier or similar? Use cubic with offset)
    if (blendType == 2) {
        if (numFrames == 1) {
            *outResult = *(float*)((int)keyframes + 0x10);
            return (float)numFrames;
        }
        ushort currentIdx = *(ushort*)((float*)this + 1);
        if (currentIdx == numFrames) {
            *outResult = *(float*)((int)keyframes + -4 + (uint)numFrames * 0x14);
            return 1.0f;
        }
        float t = time - *(float*)((int)keyframes + -0x14 + (uint)currentIdx * 0x14);
        int baseOffset = (int)keyframes + -0x14 + (uint)currentIdx * 0x14;
        if (t < 0.0f) {
            (**(code**)(*DAT_01205590 + 4))(); // error handler
        }
        // Cubic bezier interpolation (simplified from decompiled)
        float a = *(float*)(baseOffset + 4);
        float b = *(float*)(baseOffset + 8);
        float c = *(float*)(baseOffset + 0xC);
        float d = *(float*)(baseOffset + 0x10);
        *outResult = ((a * t + b) * t + c) * t + d;
        return 0.0f;
    }
    // Unknown blend type
    (**(code**)(*DAT_01205590 + 4))();
    *outResult = 0.0f;
    return 1.0f;
}