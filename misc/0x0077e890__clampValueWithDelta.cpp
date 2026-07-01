// FUNC_NAME: clampValueWithDelta
float10 clampValueWithDelta(float currentValue, float delta)
{
    float result = currentValue;
    if (delta != 0.0f) {
        // DAT_00d691d8 is likely a max value (e.g., 1.0f or some limit)
        // DAT_00d5ef84 is likely a speed/rate multiplier
        result = (DAT_00d691d8 - currentValue) * DAT_00d5ef84 * delta + currentValue;
        if (result <= 0.0f) {
            // If result goes below zero, return negative of current value (clamp to zero)
            return (float10)0.0f - (float10)currentValue;
        }
        if (DAT_00d691d8 <= result) {
            result = DAT_00d691d8;
        }
    }
    // Return the change from current value
    return (float10)result - (float10)currentValue;
}