// FUNC_NAME: ParameterSmoother::update

// Function address: 0x006c9880
// Role: Interpolates a float parameter over time with optional curve and inversion.
//   This object (param1) holds state (current time, curve multiplier).
//   param2 is a "range" object containing min, max, duration, and curve power.
//   param3 is output pointer for the interpolated value.
//   param4 is a master volume/speed factor (may contain bit flags?).
//   param5 is delta time to advance.
//   param6 is an additional multiplier (e.g., volume gain).

#include <cstdint>

// Global symbols from the game (addresses assumed)
extern float DAT_00d5efd0;          // threshold for early exit
extern uint32_t DAT_00e44680;       // mask for bit-field check in param4
extern float DAT_00e50fbc;          // master curve multiplier
extern float DAT_00e445c8;          // additional scale factor
extern bool DAT_0112a7a4;           // flag to invert output (e.g., 1.0 - result)
extern float DAT_00e44564;          // max value (e.g., 1.0)

// Forward declarations of called functions
bool IsPaused();                     // 0x00410eb0
float MathClamp(float value);        // 0x004a1580 (clamps to [0,1] or similar)

class ParameterSmoother {
public:
    // +0x60: curve multiplier applied in interpolation
    float m_curveMultiplier;
    // +0x78: current progress time (accumulated from deltas)
    float m_currentTime;

    void update(void* rangeObj, float* outValue, float masterFactor, float deltaTime, float gain)
    {
        float fVar3;

        // Unusual bitwise check on masterFactor (treat as integer bits)
        if ((float)((uint32_t)masterFactor & DAT_00e44680) <= DAT_00d5efd0) {
            // If flag condition met, reset progress to zero and output zero
            fVar3 = 0.0f;
            m_currentTime = 0.0f;
        } else {
            // Accumulate delta time
            m_currentTime += deltaTime;

            // Clamp progress to range duration (stored at rangeObj+0x10)
            float duration = *(float*)((uint8_t*)rangeObj + 0x10);
            if (m_currentTime > duration) {
                m_currentTime = duration;
            }

            // Calculate interpolation factor (0 to 1)
            fVar3 = m_currentTime / duration;
        }

        // Check pause state
        if (!IsPaused()) {
            // Interpolate between min (rangeObj+0x8) and max (rangeObj+0xc) using factor
            float rangeMin = *(float*)((uint8_t*)rangeObj + 0x8);
            float rangeMax = *(float*)((uint8_t*)rangeObj + 0xC);
            float interpolated = (rangeMax - rangeMin) * fVar3 + rangeMin;

            // Apply global multipliers (masterCurve, scaleFactor) and masterFactor
            float result = interpolated * DAT_00e50fbc * DAT_00e445c8 * masterFactor;

            // Invert if flag is set
            if (DAT_0112a7a4) {
                result = DAT_00e44564 - result;
            }

            // Apply clamp (double precision internally) and output
            float target = *outValue;
            float diff = result - target;
            diff = MathClamp(diff);                                         // clamp diff?
            float curvePower = *(float*)((uint8_t*)rangeObj + 0x24);
            float step = diff * curvePower * m_curveMultiplier * gain + target;
            *outValue = MathClamp(step);
        } else {
            // Paused: directly compute output without interpolation
            float rangeMax = *(float*)((uint8_t*)rangeObj + 0xC);
            float result = rangeMax * DAT_00e445c8 * masterFactor * gain;
            if (DAT_0112a7a4) {
                *outValue = DAT_00e44564 - result;
            } else {
                *outValue = result;
            }
        }
    }
};