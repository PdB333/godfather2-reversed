// FUNC_NAME: VehicleInput::applyReverseSpeedLimit
// Address: 0x006c1120
// Reads a float field at this+0x1a8 (likely maxReverseSpeed or currentThrottle) and
// returns it multiplied by a reverse multiplier if the input is negative and the
// current speed exceeds a threshold.

float VehicleInput::applyReverseSpeedLimit(float inputAxis, float currentSpeed)
{
    // +0x1a8: some float state (likely desired throttle/steering value)
    float result = *(float *)(this + 0x1a8);

    // If the input indicates reverse (negative) and the global speed threshold
    // (DAT_00e44828) is less than or equal to currentSpeed, apply a reverse speed limiter
    if ((inputAxis < 0.0f) && (DAT_00e44828 <= currentSpeed))
    {
        // DAT_0d5eee4: reverse multiplier (e.g. 0.5f to cap reverse speed)
        result *= DAT_0d5eee4;
    }

    return result;
}