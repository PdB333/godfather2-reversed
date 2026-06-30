// FUNC_NAME: AnimationInterpolator::interpolateFrame
// Takes a blend time t (clamped 0..max), a per-component scale vector, and outputs an interpolated quaternion to out.
// this points to an array of Frame structures (size 0x20) with a frame count short at offset 0x1c of the first element? (unusual layout)
int __thiscall AnimationInterpolator::interpolateFrame(float t, const float* scaleVector, float* outQuat)
{
    static float g_maxBlendTime = DAT_00e2b1a4; // global maximum blend time
    float zero = 0.0f;
    
    // Clamp t to [0, maxBlendTime]
    if (t > 0.0f) {
        if (t > g_maxBlendTime)
            t = g_maxBlendTime;
    } else {
        t = 0.0f;
    }
    
    // Calculate fractional frame index based on count
    short frameCount = *(short*)((char*)this + 0x1c); // +0x1c: number of frames
    float scaledT = (float)(int)frameCount * t;
    int idx0 = (int)scaledT;          // integer part
    float frac = scaledT - (float)idx0; // fractional part (lerp factor)
    
    if (idx0 >= frameCount) {
        idx0 = frameCount - 1;
        frac = g_maxBlendTime;  // actual maximum? (clamp fraction)
    }
    
    // Read short from each frame's first 2 bytes (frame index mapping)
    int idx1 = *(short*)((char*)this + idx0 * 0x20 + 0x3c); // +0x3c: short within frame structure
    int idxPrev = idx1 - 1;
    if (idxPrev < 0) idxPrev = 0;
    
    // Pointers to the two frames: prev and current (based on mapped indices)
    float* framePrev = (float*)((char*)this + idxPrev * 0x20);
    float* frameCurr = (float*)((char*)this + idx1  * 0x20);
    
    // Scale previous frame's components by scaleVector
    float xPrev = framePrev[0] * scaleVector[0];
    float yPrev = framePrev[1] * scaleVector[1];
    float zPrev = framePrev[2] * scaleVector[2];
    float wPrev = framePrev[3]; // not used in lerp? (but stored for later)
    
    // Scale current frame's components by scaleVector
    float xCurr = frameCurr[0] * scaleVector[0];
    float yCurr = frameCurr[1] * scaleVector[1];
    float zCurr = frameCurr[2] * scaleVector[2];
    float wCurr = frameCurr[3];
    
    // Linear interpolation between scaled frames
    outQuat[0] = frac * (xCurr - xPrev) + xPrev;
    outQuat[1] = frac * (yCurr - yPrev) + yPrev;
    outQuat[2] = frac * (zCurr - zPrev) + zPrev;
    outQuat[3] = frac * (wCurr - wPrev) + wPrev;
    outQuat[3] = g_maxBlendTime; // overwritten to max time (intentional? maybe weight)
    
    // Internal update call
    FUN_00414aa0(); // likely updates some internal state (e.g., blend timer)
    
    outQuat[7] = 0.0f; // clear extra channel (index 7)
    return 1;
}