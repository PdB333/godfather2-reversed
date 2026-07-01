// FUNC_NAME: SomeClass::remapValueToRange
// Function address: 0x007f1370
// Reads a float from (this->m_pUnknown + 0x4c), clamps it to a global range,
// then linearly remaps it to an output range defined by global constants.
// Used for mapping gameplay values to a different scale (e.g., health to damage overlay opacity).

float SomeClass::remapValueToRange()
{
    // Read source value from sub-object at offset +0x4c
    float sourceValue = *(float*)(*(int*)(this + 0x4) + 0x4C);  // this->m_pUnknown->someFloat

    float clampedValue;

    // global input range constants
    const float INPUT_MIN = DAT_00d5ef88;          // 0x00d5ef88
    const float INPUT_MAX = DAT_00d70058;          // 0x00d70058
    const float INPUT_RANGE = _DAT_00e53684;       // 0x00e53684  (should be INPUT_MAX - INPUT_MIN)

    // output range constants
    const float OUTPUT_MIN = DAT_00d5cf70;         // 0x00d5cf70
    const float OUTPUT_RANGE = _DAT_00e53688;      // 0x00e53688

    // Clamp source value to [INPUT_MIN, INPUT_MAX]
    if (sourceValue <= INPUT_MAX) {
        if (sourceValue >= INPUT_MIN) {
            clampedValue = sourceValue;  // within range
        } else {
            clampedValue = INPUT_MIN;    // below min (value at 0x00d70054 is same as INPUT_MIN)
        }
    } else {
        clampedValue = INPUT_MAX;        // above max
    }

    // Remap: (clampedValue - INPUT_MIN) / INPUT_RANGE * OUTPUT_RANGE + OUTPUT_MIN
    float normalized = (clampedValue - INPUT_MIN) / INPUT_RANGE;
    return normalized * OUTPUT_RANGE + OUTPUT_MIN;
}