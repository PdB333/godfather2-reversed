// FUNC_NAME: AnimationController::computeBlendedValue
float __thiscall AnimationController::computeBlendedValue(float time, float seed, float amplitude)
{
    float x, y;
    float progress = *(float *)(this + 0x2dc);  // +0x2dc: animation progress [0,1]
    float baseX = *(float *)(this + 0x104);     // +0x104: base keyframe X
    float baseY = *(float *)(this + 0x108);     // +0x108: base keyframe Y
    float lowX = *(float *)(this + 0x1c0);      // +0x1c0: low bound X
    float lowY = *(float *)(this + 0x1c4);      // +0x1c4: low bound Y
    float highX = *(float *)(this + 0x1d0);     // +0x1d0: high bound X
    float highY = *(float *)(this + 0x1d4);     // +0x1d4: high bound Y
    bool useBlend = *(char *)(this + 0x2bc) != '\0'; // +0x2bc: blend mode flag

    extern float _DAT_00d5780c; // threshold for blend transition
    extern float _DAT_00e50e70, _DAT_00e50e74, _DAT_0112a784, _DAT_00e50f7c; // oscillation parameters

    // Step 1: interpolate base position based on blend flag and progress
    if (!useBlend) {
        x = baseX;
        y = baseY;
    } else {
        if (_DAT_00d5780c < progress) {
            // Above threshold: lerp from base to high
            x = (highX - baseX) * (progress - _DAT_00d5780c) + baseX;
            y = (highY - baseY) * (progress - _DAT_00d5780c) + baseY;
        } else {
            // Below threshold: lerp from low to base
            x = (baseX - lowX) * progress + lowX;
            y = (baseY - lowY) * progress + lowY;
        }
    }

    // Step 2: apply a base transform/noise function to the blended position
    double result = (double) FUN_006c89b0(x, y, time);

    // Step 3: if blending is active, add an oscillating component
    if (useBlend) {
        double noisePhase = (double) FUN_006c36e0(x, y);
        double maxAmplitude = (double) FUN_006c37f0();
        double oscillation = (double) FUN_006c91c0(seed, _DAT_00e50e70, _DAT_00e50e74,
                                                    _DAT_0112a784, _DAT_00e50f7c);
        // Amplitude blend: oscillation * amplitude + threshold, then scale by (phase + result)
        double blended = (oscillation * (double)amplitude + (double)_DAT_00d5780c) *
                         (double)(noisePhase + (double)result);
        // Clamp to maximum allowed noise amplitude
        if (blended <= (double)maxAmplitude) {
            result = blended;
        } else {
            result = (double)maxAmplitude;
        }
    }

    return result;
}