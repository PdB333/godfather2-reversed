// FUNC_NAME: EARSObject::updateSmoothValue
float __thiscall EARSObject::updateSmoothValue(float delta, float target, float param4)
{
    // Offset of smoothed variable within object
    float* pCurrentValue = (float*)((uint8_t*)this + 0x84);

    // Constants likely from global data (time scale, interpolation factor)
    float const1 = DAT_00e52fec;
    float const2 = _DAT_00e52ff8;

    // Pointer to delta (used as in/out parameter by called functions)
    float* pDelta = &delta;

    // Error between target and current value
    float error = target - *pCurrentValue;

    // First smoothing step: possibly clamps or scales error based on delta and constant
    float smoothed = (float)FUN_006d6350(error, const1, delta, pDelta, 0);

    // Second step: combine smoothed result with another constant and param4
    float result = smoothed * const2 + param4;
    FUN_007992a0(result, const1, delta, pDelta, 0);

    // Update the current value by the (possibly modified) delta
    *pCurrentValue = delta + *pCurrentValue;

    return delta; // returns the delta (possibly modified by smoothing)
}