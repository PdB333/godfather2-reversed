// FUNC_NAME: MathUtil::randomQuadraticLerp
// Function at 0x006c91c0: Computes a quadratic ease with random variation and clamping.
// Used by many AI/vehicle functions for smooth randomized transitions.

extern float DAT_00d5f00c; // Global scaling factor for random influence
extern float _DAT_00d577a0; // Epsilon threshold for clamping check (likely 0.0f)
extern double __cdecl __fastcall randomDouble(); // FUN_00b99fcb: returns a double between 0.0 and 1.0

float MathUtil::randomQuadraticLerp(float input, float minInput, float maxInput, float minOutput, float maxOutput)
{
    float clampedInput;

    // Clamp input between minInput and maxInput
    if (input < minInput) {
        clampedInput = minInput;
        if (maxInput <= minInput) {
            clampedInput = maxInput;
        }
    } else {
        clampedInput = input;
    }

    // Normalize clampedInput within [minInput, maxInput] range
    float normalized = (clampedInput - minInput) / (maxInput - minInput);
    double factor = (double)(normalized * DAT_00d5f00c) * randomDouble();

    // Apply quadratic ease: square the factor and map to output range
    float eased = (float)(factor * factor) * (maxOutput - minOutput) + minOutput;

    // Clamp the result to [minOutput, maxOutput]
    if (maxOutput - minOutput <= _DAT_00d577a0) {
        // If output range is very small, snap to min or max
        if (eased <= maxOutput) {
            return maxOutput;
        }
        if (eased < minOutput) {
            eased = minOutput;
        }
    } else {
        // Normal clamping
        if (eased < minOutput) {
            eased = minOutput;
        } else if (eased > maxOutput) {
            eased = maxOutput;
        }
    }

    return eased;
}