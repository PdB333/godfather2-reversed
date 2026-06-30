// FUNC_NAME: clampValueWithMaxCap
float clampValueWithMaxCap(float input, float multiplier)
{
    // _DAT_0112a7a8 appears to be a global scaling factor (e.g., time delta or base value)
    // _DAT_00d5780c is a global maximum cap value
    float scaled = (input / _DAT_0112a7a8) * multiplier;
    if (_DAT_00d5780c < scaled) {
        return (float)_DAT_00d5780c;
    }
    return (float)scaled;
}