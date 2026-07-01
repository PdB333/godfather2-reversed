// FUNC_NAME: clampAndBlendValue
// Address: 0x007f6c40
// Purpose: Applies dead zone and bounds checking for analog stick input;
//          blends between two raw input values and optionally applies an offset.
// Dependencies: Uses global floats at fixed addresses (likely input system globals).

// Forward declaration of utility function at 0x0056aee0
float computeScaledValue(float raw, float threshold, float current);

// Global constants (from data sections)
extern float g_deadZoneThreshold;      // 0x00d5d70c
extern float g_maxValidValue;          // 0x00d5f00c (upper bound)
extern float g_minValidValue;          // 0x00e446a0 (lower bound, likely negative)
extern float g_correctionOffset;       // 0x00d5eeec (offset added to inputValue when correction applied)

void __cdecl clampAndBlendValue(float inputValue, float rawValue1, float rawValue2) {
    float result;
    float current = inputValue;

    // First attempt: scale rawValue1 using dead zone threshold
    result = computeScaledValue(rawValue1, g_deadZoneThreshold, current);

    // Check if result is outside the valid range (e.g., outside analog stick physical bounds)
    if ((result > g_maxValidValue) || (result < g_minValidValue)) {
        // Second attempt: fall back to rawValue2
        result = computeScaledValue(rawValue2, g_deadZoneThreshold, current);

        // If the fallback is within expected bounds, apply a correction
        if ((result <= g_maxValidValue) && (result >= g_minValidValue)) {
            computeScaledValue(inputValue + g_correctionOffset, g_deadZoneThreshold, current);
        }
    }
    // Note: no explicit return value – function modifies global state or performs side effects.
}