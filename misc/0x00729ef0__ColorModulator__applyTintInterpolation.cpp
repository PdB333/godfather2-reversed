// FUNC_NAME: ColorModulator::applyTintInterpolation
void __thiscall ColorModulator::applyTintInterpolation(float *pOutputColorArray, int *pContext) {
    float interpolationFactor = 0.0f;

    // Check if context is valid and contains active state
    if ((*pContext != 0) &&
        (int statePtr = *(int *)(*pContext + 0x1ed8); statePtr != 0 && statePtr != 0x48) &&
        (pContext[1] != 0)) {
        // Get interpolation value from context's second pointer
        float rawFactor = *reinterpret_cast<float *>(pContext[1] + 0x1ed4);
        interpolationFactor = static_cast<float>(FUN_008be840(rawFactor)); // extended precision conversion
    }

    // For each of the four color channels, interpolate between stored min and max, then multiply by original value
    pOutputColorArray[0] = ((*(float *)(this + 0x5c) - *(float *)(this + 0x58)) * interpolationFactor +
                            *(float *)(this + 0x58)) * pOutputColorArray[0];
    pOutputColorArray[1] = ((*(float *)(this + 0x64) - *(float *)(this + 0x60)) * interpolationFactor +
                            *(float *)(this + 0x60)) * pOutputColorArray[1];
    pOutputColorArray[2] = ((*(float *)(this + 0x6c) - *(float *)(this + 0x68)) * interpolationFactor +
                            *(float *)(this + 0x68)) * pOutputColorArray[2];
    pOutputColorArray[3] = ((*(float *)(this + 0x74) - *(float *)(this + 0x70)) * interpolationFactor +
                            *(float *)(this + 0x70)) * pOutputColorArray[3];
}