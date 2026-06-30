// FUNC_NAME: smoothTowardsWithAccelerationLimit
// This function smooths a value towards a target with acceleration limiting and nonlinear scaling.
// Used in camera/vehicle movement to prevent instant changes.
// Parameters:
//   current - current value (param_1)
//   target  - desired value (param_2)
//   deltaTime - time step or responsiveness factor (param_3)
// Returns: new smoothed value (original param_1 + clamped delta)

// Static globals (initialized elsewhere, likely in the camera/controller module)
extern float s_maxDeltaThreshold;  // _DAT_00d577a0 - if delta exceeds this, apply smoothing
extern float s_rangeUpper;         // DAT_00e51178 - upper bound for nonlinear mapping
extern float s_rangeLower;         // DAT_00e511a8 - lower bound for nonlinear mapping
extern float s_coeffA;             // _DAT_00d5780c - coefficient A
extern float s_coeffB;             // DAT_00e511a4 - coefficient B
extern float s_minDeltaClamp;      // DAT_00e44564 - minimum delta clamping value

float smoothTowardsWithAccelerationLimit(float current, float target, float deltaTime)
{
    float delta = target - current;

    if (s_maxDeltaThreshold < delta)
    {
        float range = s_rangeUpper - s_rangeLower; // fVar2 = DAT_00e51178 - DAT_00e511a8

        float scaleFactor;
        if (range <= current)
        {
            // current is within the range [range, s_rangeUpper]
            if (current < s_rangeUpper)
            {
                // Normalize current within [range, s_rangeUpper]
                float normalized = (current - range) / (s_rangeUpper - range); // fVar2 = (param_1 - fVar2) / (DAT_00e51178 - fVar2)
                // Interpolate between s_coeffA and something? Original: fVar1 = DAT_00e511a4 * fVar2 + (_DAT_00d5780c - fVar2)
                scaleFactor = s_coeffB * normalized + (s_coeffA - normalized);
            }
            else
            {
                // For current >= s_rangeUpper, scaleFactor is 0? Actually not handled, fall through to previous scaleFactor? 
                // The original code only sets fVar1 inside the if(current < s_rangeUpper) block, else it keeps previous value? 
                // But fVar1 was not initialized. However, in that case the condition (current < s_rangeUpper) fails, so scaleFactor is undefined.
                // Assuming no scaling (scaleFactor = 0) or previous? But original code doesn't set fVar1 outside.
                // Possibly this path is never taken because current < s_rangeUpper when range <= current? 
                // Actually if range <= current, then current >= range, so it could be >= s_rangeUpper. 
                // If current >= s_rangeUpper, then normalization would be >=1, but the if condition fails, so scaleFactor is uninitialized. 
                // Could be a bug or dead code. We'll set to 0 as a safe default.
                scaleFactor = 0.0f;
            }
        }
        else
        {
            // current is below the lower bound of the range
            float currentOverRange = current / range; // param_1 / fVar2
            scaleFactor = (s_coeffA - currentOverRange) * s_coeffB + currentOverRange;
        }

        // Apply deltaTime scaling (param_3)
        float scaledDelta = scaleFactor * deltaTime; // fVar1 = fVar1 * param_3

        if (scaledDelta < delta)
        {
            // Clamp the new delta to the scaled value, return current + scaledDelta
            return current + scaledDelta;
        }

        // If scaledDelta exceeds delta, we might need to clamp by s_minDeltaClamp
        if (delta < s_minDeltaClamp - scaledDelta)
        {
            delta = s_minDeltaClamp - scaledDelta;
        }
    }
    // Default: return current + delta (i.e., target)
    return current + delta;
}