// FUNC_NAME: ControllerDevice::applyAnalogCurve
float __thiscall ControllerDevice::applyAnalogCurve(void* this, char axisFlag, float inputValue)
{
    // Check if some override mode is active (e.g., simplified scaling)
    bool isSimple = FUN_00410eb0(this) != 0; // likely isInverted or isDeadzoneDisabled
    if (isSimple) {
        // Simple linear scaling by constant
        return (float)_DAT_00e510e8 * inputValue;
    }

    // Normal curve processing
    float clampedValue;
    // Clamp inputValue between two global thresholds (deadzone and saturation)
    float thresholdMin = DAT_00d5ccf8;
    float thresholdMax = _DAT_00d5780c;
    if (inputValue >= thresholdMin && inputValue <= thresholdMax) {
        clampedValue = inputValue;
    } else if (inputValue < thresholdMin) {
        clampedValue = thresholdMin;
    } else {
        clampedValue = thresholdMax;
    }

    // Take absolute value of the clamped input (mask likely 0x7FFFFFFF to clear sign)
    // The original code does bitwise AND on the raw float bits to strip sign
    unsigned int bits = *(unsigned int*)&clampedValue;
    bits &= DAT_00e44680;                // mask (probably 0x7FFFFFFF)
    float absValue = *(float*)&bits;

    // Choose interpolation endpoints based on axis flag
    float outMin, outMax;
    if (axisFlag != 0) {
        outMin = _DAT_00e510ec;          // min output for this axis
        outMax = _DAT_00e510f0;          // max output for this axis
    } else {
        outMin = _DAT_00e510e4;          // min output for other axis
        outMax = _DAT_00e510e8;          // max output
    }

    // Linear interpolation: outMin + (outMax - outMin) * absValue
    return (1.0f - absValue) * outMin + outMax * absValue;
}