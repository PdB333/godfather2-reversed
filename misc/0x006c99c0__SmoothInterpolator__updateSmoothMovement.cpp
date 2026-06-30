// FUNC_NAME: SmoothInterpolator::updateSmoothMovement

#include <cmath> // For fabs, clamp

// External globals (from the game executable)
extern float gSpeedMultiplier;      // _DAT_00e50fb8
extern float gTimeScale;            // DAT_00e445c8
extern float gEpsilon;              // DAT_00d5efd0
extern unsigned int gAbsMask;       // DAT_00e44680 (0x7FFFFFFF)
extern byte gInvertFlag;            // DAT_0112a7a5
extern float gMaxOutput;            // DAT_00e44564

// Forward declaration of helper functions (addresses known)
extern bool isSmoothingEnabled();           // FUN_00410eb0
extern float clampFloat(float value);       // FUN_004a1580 (clamp to [0.0, 1.0]? or something similar)

// The class that contains the smoothing state
class SmoothInterpolator {
public:
    // Offsets from 'this'
    // +0x60 : float speedFactor
    // +0x74 : float accumulator (time or progress)

    // Update the smoothing calculation
    // @param params: array of parameters (size at least 9)
    //   params[0] = start value (min)
    //   params[1] = end value (max)
    //   params[4] = maxTime (duration for full interpolation)
    //   params[8] = smoothing clamp (max change per second)
    // @param output: reference to the current output value (modified in place)
    // @param deltaTime: frame time (used to compute target position)
    // @param deltaInc: increment to add to accumulator
    // @param multiplier: additional scaling factor for the smoothing
    void updateSmoothMovement(const float* params, float& output,
                              float deltaTime, float deltaInc, float multiplier) {
        // Check if deltaTime is negligible (absolute value < epsilon)
        if ((float)((unsigned int)deltaTime & gAbsMask) <= gEpsilon) {
            // Reset accumulator to zero
            accumulator = 0.0f;
            // Also set a flag at +0x74 to 0? The decompiled sets *(undefined4*)(param_1+0x74)=0
            // That's already done by setting accumulator
        } else {
            // Accumulate time
            accumulator += deltaInc;
            // Clamp accumulator to maxTime (params[4])
            if (accumulator > params[4])
                accumulator = params[4];
        }

        // Compute interpolation factor based on accumulator
        float progress = accumulator / params[4];

        // Branch depending on a global toggle
        if (isSmoothingEnabled()) {
            // Simple direct calculation: use only the end value
            float target = params[1] * gTimeScale * deltaTime * multiplier;
            // Invert if global flag set
            if (gInvertFlag == 0)
                output = gMaxOutput - target;
            else
                output = target;
            return;
        }

        // Complex smoothed interpolation

        // Compute the linear target value (interpolated between start and end)
        float linearTarget = (params[1] - params[0]) * progress + params[0];
        // Scale by time and multipliers
        float scaledTarget = linearTarget * gSpeedMultiplier * gTimeScale * deltaTime;
        // Optionally invert
        if (gInvertFlag == 0)
            scaledTarget = gMaxOutput - scaledTarget;

        // Apply spring-like smoothing: clamp the difference between target and current output,
        // then add a fraction of the clamped difference to current output, then clamp again.
        float clampedDiff = clampFloat(scaledTarget - output);
        float smoothedValue = clampFloat(clampedDiff * params[8] * speedFactor * multiplier + output);

        // Set the output
        output = smoothedValue;
    }

private:
    // Members (inferred from offsets)
    float speedFactor;    // +0x60
    float accumulator;    // +0x74
};