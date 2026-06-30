// FUNC_NAME: AnimationTrack::evaluateKeyframes
extern void* g_animationSystem; // *DAT_012055a8
extern void* g_errorHandler;    // *DAT_01205590

// Keyframe: 16 bytes, time + 3 floats
struct AnimationKeyframe {
    float time;      // 0x00
    float valueX;    // 0x04
    float valueY;    // 0x08
    float valueZ;    // 0x0C
};

// This is likely a member function called with this in EAX (__thiscall)
// Parameter param_1 is a context/object to receive the interpolated value
int __thiscall AnimationTrack::evaluateKeyframes(void* context) {
    // Offset 0: current time (float)
    float currentTime = *(float*)this;
    // Offset 4: current key index (short)
    short currentKeyIndex = *(short*)((char*)this + 4);
    // Offset 6: key count (short)
    short keyCount = *(short*)((char*)this + 6);
    // Offset 12: pointer to keyframe array
    AnimationKeyframe* keys = *(AnimationKeyframe**)&((float*)this)[3];

    // Callback for output: (*DAT_012055a8)[0x34] is a function (void*)(float x, float y, float z, void* context)
    typedef void (*OutputCallback)(float, float, float, void*);
    OutputCallback output = (OutputCallback)(*(void**)(*(int*)g_animationSystem + 0x34));

    // Error handler: (*DAT_01205590)[4]
    typedef void (*ErrorFunc)();
    ErrorFunc error = (ErrorFunc)(*(void**)(*(int*)g_errorHandler + 4));

    if (keyCount == 0) {
        output(0.0f, 0.0f, 0.0f, context);
        return 1;
    }

    // Ensure current key index is valid (expected to be 1 initially?)
    if (currentKeyIndex != 1) {
        error(); // Log or assert
    }

    if (keyCount == 1) {
        // Single key: output its value
        output(keys->valueX, keys->valueY, keys->valueZ, context);
        return 1;
    }

    if (currentKeyIndex == keyCount) {
        // At last key: output its value directly
        AnimationKeyframe* lastKey = &keys[keyCount - 1];
        output(lastKey->valueX, lastKey->valueY, lastKey->valueZ, context);
        return 1;
    }

    // Interpolation between current and next key
    AnimationKeyframe* currKey = &keys[currentKeyIndex];
    AnimationKeyframe* prevKey = &keys[currentKeyIndex - 1];
    float prevTime = prevKey->time;
    float nextTime = currKey->time;
    float t = (currentTime - prevTime) / (nextTime - prevTime);

    // Clamp check (using global thresholds, likely 0.0 and 1.0)
    extern float g_tMin; // DAT_00e2b05c
    extern float g_tMax; // DAT_00e2b1a4
    if (t < g_tMin || t > g_tMax) {
        error();
    }

    // Linear interpolation
    float interpolatedX = prevKey->valueX + (currKey->valueX - prevKey->valueX) * t;
    float interpolatedY = prevKey->valueY + (currKey->valueY - prevKey->valueY) * t;
    float interpolatedZ = prevKey->valueZ + (currKey->valueZ - prevKey->valueZ) * t;

    output(interpolatedX, interpolatedY, interpolatedZ, context);
    return 0;
}