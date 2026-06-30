// FUNC_NAME: AnimationInterpolator::updateValue

#include <cstdint>
#include <cmath>

// Forward declarations for unknown functions (likely from engine math library)
extern bool SomeGlobalCheck(); // FUN_00410eb0 - returns a char, likely indicating playback direction or pause
extern float MathAbsf(float); // FUN_004a1580 - absolute value (fabs)

// Global variables referenced (offsets unknown, placed here for reconstruction)
extern uint32_t g_SignMask;         // DAT_00e44680 - mask for extracting sign bit from float
extern float     g_Threshold;       // DAT_00d5efd0 - comparison threshold
extern float     g_GlobalScaleA;    // DAT_00e50fbc - first global multiplier
extern float     g_GlobalScaleB;    // DAT_00e445c8 - second global multiplier
extern bool      g_IsInverted;      // DAT_0112a7a4 - invert flag
extern float     g_InversionBase;   // DAT_00e44564 - base value for inversion

class InterpolatorParams {
public:
    float startValue;          // +0x08
    float endValue;            // +0x0C
    float duration;            // +0x10
    float accelerationFactor;  // +0x24 - ease/spring factor
};

class AnimationInterpolator {
public:
    float elapsedTime;   // +0x78 - accumulated time
    float internalScale; // +0x60 - per‑instance multiplier

    // __thiscall
    // param1 = this (AnimationInterpolator)
    // param2 = params (InterpolatorParams)
    // param3 = outValue (float*)
    // param4 = inputParam (float) – used both as condition mask and scalar
    // param5 = deltaTime (float)
    // param6 = extraMultiplier (float)
    void updateValue(InterpolatorParams* params, float* outValue,
                     float inputParam, float deltaTime, float extraMultiplier) {
        float ratio;

        // Bitwise test: check if the sign‑bit of inputParam (interpreted as uint32)
        // results in a value <= threshold. Possibly checks for negative or NaN.
        if ( ((uint32_t)inputParam & g_SignMask) <= (uint32_t)g_Threshold ) {
            ratio = 0.0f;
            elapsedTime = 0.0f;
        } else {
            elapsedTime += deltaTime;
            if (params->duration < elapsedTime) {
                elapsedTime = params->duration;
            }
            ratio = elapsedTime / params->duration;
        }

        bool playbackForward = SomeGlobalCheck(); // returns 0/1
        if (!playbackForward) {
            // Normal ease branch:
            // Linearly interpolate between start and end based on ratio,
            // then apply global scale factors and the input scalar.
            float target = ( (params->endValue - params->startValue) * ratio + params->startValue )
                           * g_GlobalScaleA * g_GlobalScaleB * inputParam;

            if (g_IsInverted) {
                target = g_InversionBase - target;
            }

            // Compute current output value using a smooth/damped approach:
            // difference from current outValue, scaled by acceleration factors,
            // then added back to outValue (absolute value used to avoid overshoot).
            float diff  = MathAbsf(target - *outValue);
            float newVal = MathAbsf(diff * params->accelerationFactor * internalScale * extraMultiplier + *outValue);
            *outValue = newVal;
        } else {
            // Simple branch: just scale endValue directly.
            float simple = params->endValue * g_GlobalScaleB * inputParam * extraMultiplier;
            *outValue = g_IsInverted ? (g_InversionBase - simple) : simple;
        }
    }
};