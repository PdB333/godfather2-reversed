// FUNC_NAME: computeSmoothedBlendFactor

#include <cstdint>

// Assumed global constant (likely 1.0f)
extern float _DAT_00d5780c;

// Forward declarations of helper functions
// Returns a pointer to an animation manager singleton (with virtual functions)
void* getAnimationManager();
// Retrieves animation blend range: end, start, currentTime
void getAnimationBlendRange(float& end, float& start, float& current);

// Function at 0x00702d70
// Computes a smoothed interpolation factor by clamping a scaled time value
float computeSmoothedBlendFactor()
{
    void* animMgr = getAnimationManager();
    if (animMgr != nullptr) {
        float currentTime;                     // local_4
        float blendVals[4];                    // local_14 (indices 0..3 used)
        float& end = blendVals[3];
        float& start = currentTime;
        float& rawTime = blendVals[0];

        getAnimationBlendRange(end, start, rawTime);

        // Virtual call at vtable offset 0x240 – likely getTimeScale()
        float timeScale = (*(float (__thiscall**)(void*))(*(uintptr_t*)animMgr + 0x240))(animMgr);

        // Multiply to get scaled time
        float scaled = timeScale * rawTime;
        blendVals[0] = scaled;
        blendVals[1] = _DAT_00d5780c;   // Upper clamp constant (usually 1.0f)
        blendVals[2] = 0.0f;            // Lower clamp

        float* factorPtr;
        if (scaled <= 1.0f) {
            factorPtr = &blendVals[2];  // 0.0f
            if (scaled >= 0.0f) {
                factorPtr = &blendVals[0]; // use scaled value
            }
        } else {
            factorPtr = &blendVals[1];  // constant (1.0f)
        }

        // Lerp: start + (end - start) * factor
        return start + (end - start) * (*factorPtr);
    }
    return 0.0f;
}