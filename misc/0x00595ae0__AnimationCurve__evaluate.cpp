// FUNC_NAME: AnimationCurve::evaluate
// Function address: 0x00595ae0
// Role: Evaluate animation curve at a given time, output interpolated quaternion/vector

#include <cstdint>

// Forward declarations for the likely global function table and logging
struct DebugLogger; // singleton with vtable
extern DebugLogger* gDebugLogger; // DAT_012055a8
extern DebugLogger* gErrorLogger; // DAT_01205590

struct AnimationKeyframe {
    float time;   // +0x00
    float x;      // +0x04
    float y;      // +0x08
    float z;      // +0x0C
    float w;      // +0x10
};

class AnimationCurve {
public:
    short getNumKeyframes() const { return *(const short*)(this + 6); }
    short getCurrentIndex() const { return *(const short*)(this + 1); }
    short getBlendType() const    { return *(const short*)(this + 2); }
    float getCurrentTime() const  { return *(const float*)this; }
    const AnimationKeyframe* getKeyframes() const { return *(const AnimationKeyframe**)(this + 0xC); }

    // Evaluate the curve, output result into outVec
    // param_1 is a string for logging context (e.g., "Evaluating curve")
    bool evaluate(const char* debugContext, float* outVec /* x,y,z,w */);
};

// Verify keyframe size: each is 0x14 = 20 bytes as used in code
static_assert(sizeof(AnimationKeyframe) == 20, "Keyframe struct size mismatch");

// Global clamp thresholds from data
extern const float gClampMin; // DAT_00e2b05c
extern const float gClampMax; // DAT_00e2b1a4

bool AnimationCurve::evaluate(const char* debugContext, float* outVec)
{
    short numKeyframes = getNumKeyframes();
    const AnimationKeyframe* keyframes = getKeyframes();
    float currentTime = getCurrentTime();

    // If no keyframes, return identity quaternion (1,0,0,0)
    if (numKeyframes == 0) {
        outVec[0] = 1.0f; // w
        outVec[1] = 0.0f;
        outVec[2] = 0.0f;
        outVec[3] = 0.0f;
        // Log "no keyframes"
        gDebugLogger->printf(0x595b1c, debugContext);
        return true;
    }

    // Check blend type (should be 2 for linear interpolation)
    if (getBlendType() != 2) {
        gErrorLogger->printf(0x595b3b, debugContext);
    }

    // If only one keyframe, just return it
    if (numKeyframes == 1) {
        const AnimationKeyframe& kf = keyframes[0];
        outVec[0] = kf.x;
        outVec[1] = kf.y;
        outVec[2] = kf.z;
        outVec[3] = kf.w;
        gDebugLogger->printf(0x595b74, debugContext, 
                             kf.w, kf.z, kf.y, kf.x); // note order
        return true;
    }

    short currentIndex = getCurrentIndex();
    // If current index is the last keyframe (i.e., at end), return last keyframe
    if (currentIndex == numKeyframes) {
        const AnimationKeyframe& kf = keyframes[numKeyframes - 1];
        outVec[0] = kf.x;
        outVec[1] = kf.y;
        outVec[2] = kf.z;
        outVec[3] = kf.w;
        gDebugLogger->printf(0x595bbe, debugContext);
        return true;
    }

    // Index into keyframes (currentIndex and currentIndex+1)
    unsigned int idx = (unsigned short)currentIndex;
    const AnimationKeyframe& kfA = keyframes[idx];
    const AnimationKeyframe& kfB = keyframes[idx + 1];

    float timeA = kfA.time;
    float timeB = kfB.time;
    float t = (currentTime - timeA) / (timeB - timeA);

    // Clamp t to [0,1]
    if (t < gClampMin || t > gClampMax) {
        gErrorLogger->printf(0x595c1a, debugContext);
    }

    // Linear interpolation between keyframes
    outVec[0] = kfA.x + t * (kfB.x - kfA.x);
    outVec[1] = kfA.y + t * (kfB.y - kfA.y);
    outVec[2] = kfA.z + t * (kfB.z - kfA.z);
    outVec[3] = kfA.w + t * (kfB.w - kfA.w);

    // Store the interpolated result in local array (named 'result' for clarity)
    float result[4] = { outVec[0], outVec[1], outVec[2], outVec[3] };
    gDebugLogger->printf(0x595c4a, debugContext, result);

    // Call the interpolation function (likely a quaternion slerp or vector lerp)
    // The following call: (code)(*DAT_012055a8 + 4)(kfB.x, kfB.y, kfB.z, kfB.w);
    gDebugLogger->blend(kfB.x, kfB.y, kfB.z, kfB.w);

    // Then: (code)(*DAT_012055a8 + 0x6c)(kfB.w, &result, &debugContext, &stack0xffffffa8);
    gDebugLogger->applyBlend(kfB.w, result, debugContext);

    // Then: (code)(*DAT_012055a8 + 0x10)(&result, debugContext);
    gDebugLogger->storeResult(result, debugContext);

    // Then: (code)(*DAT_012055a8 + 0x28)(debugContext, &stack0xffffffa0);
    gDebugLogger->finalize(debugContext);

    // Then again: (code)(*DAT_012055a8 + 0x10)(&result, debugContext);
    gDebugLogger->storeResult(result, debugContext);

    return false; // indicates blending was performed
}