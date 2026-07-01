// FUNC_NAME: TimeSmoother::updateSmoothValue

#include <cmath>

// Global constants (from data section)
extern float gSpeedThreshold;          // DAT_00e44598
extern float gMinSmoothFactor;         // DAT_00d5ccf8 (lower bound)
extern float gMaxSmoothFactor;         // DAT_00d5780c (upper bound)
extern float gTimeScale;               // _DAT_00e531dc
extern uint32_t gFlagMask;             // DAT_00e44680
extern float gFlagThreshold;           // DAT_00e531d8

// External helper functions
float getCurrentTime();                // FUN_00799230
float normalizeAngle(float angle);     // FUN_006d6350
void applyOutputValue(float value);    // FUN_007ac530

class TimeSmoother {
public:
    float mLastUpdateTime;  // +0xC4

    void updateSmoothValue(float inputValue);
};

void __thiscall TimeSmoother::updateSmoothValue(float inputValue)
{
    // 1. Get current time and compute delta since last update
    float now = getCurrentTime();
    float timeDelta = now - mLastUpdateTime;

    // 2. Normalize the delta (treat as angle, wrap to [-PI, PI])
    float normalizedDelta = normalizeAngle(timeDelta);

    // 3. If time delta is below a threshold, scale by input value (speed factor)
    if (gSpeedThreshold < inputValue) {
        normalizedDelta = normalizedDelta / inputValue;
    }

    // 4. Compute ratio of (scaled delta) to a global time scale
    float ratio = normalizedDelta / gTimeScale;

    // 5. Clamp the input value using the ratio and global bounds
    float lowerBound = gMinSmoothFactor;
    float upperBound = gMaxSmoothFactor;
    float* targetPtr;
    if (ratio <= gMaxSmoothFactor) {
        if (gMinSmoothFactor <= ratio) {
            targetPtr = &inputValue;   // within range, keep original
        } else {
            targetPtr = &lowerBound;   // ratio below lower bound
        }
    } else {
        targetPtr = &upperBound;       // ratio above upper bound
    }
    inputValue = *targetPtr;

    // 6. Bitwise flag check: treat inputValue as raw bits, AND with mask
    float rawBits = (float)((uint32_t)inputValue & gFlagMask);
    if (rawBits < gFlagThreshold) {
        inputValue = 0.0f;
    }

    // 7. Apply the final value to the system and store current time
    applyOutputValue(inputValue);
    mLastUpdateTime = now;
}