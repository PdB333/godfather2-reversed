// FUNC_NAME: RumbleEffect::update

/* 0x00828080 - Update rumble effect based on elapsed time, compute and apply vibration motor value */

#include <cstdint>

class RumbleEffect {
public:
    // +0x00: vtable? not accessed here
    // +0x04 ... +0x18: unknown
    int32_t   mActive;           // +0x1c (0 = disabled)
    float     mSpeed;            // +0x24 (interpolation factor)
    float     mStrength;         // +0x28 (amplitude)
    float     mDuration;         // +0x2c (time to run, <=0 = infinite? not clamped)
    float     mRemainingTime;    // +0x30 (remaining seconds, clamped to current time)
    float     mLastUpdateTime;   // +0x34 (previous frame's global time)
    int32_t   mLoop;             // +0x38 (if non-zero, allow loop? else stop when enabled)
    uint8_t   mStopFlag;         // +0x3c (non-zero means stop? used in condition)
    
    // external globals (likely from engine time manager)
    static float& g_currentTime;      // _DAT_00d5780c (current game time in seconds)
    static float& g_previousTime;     // DAT_01205228 (previous frame's time)
    
    // extern functions
    static void getTimeInfo(float* outTime, int32_t* outType);   // FUN_00823910 - returns time info and a type selector
    static float randomFloat();                                  // FUN_004aaa30 - returns a random float [0,1)
    static void applyRumble(float motorValue);                   // FUN_004aa8c0 - applies vibration to the relevant motor
};

float RumbleEffect::g_currentTime;   // defined elsewhere
float RumbleEffect::g_previousTime;  // defined elsewhere

// Decompiled implementation
uint8_t RumbleEffect::update(int32_t param_1 /* actually this ptr */) {
    float fVar1, fVar2, fVar5, fVar6, fVar7;
    float local_8;          // time or other value from getTimeInfo
    int32_t local_4;        // type/state from getTimeInfo
    uint8_t uVar3 = 0;

    if (mActive == 0) {
        return 0;
    }

    // This call might fill local_8 with something like a time step and local_4 with a mode
    getTimeInfo(&local_8, &local_4);

    fVar5 = 0.0f;
    if (local_4 == 0) {
        // mode 0: use strength multiplied by elapsed time, plus speed * something
        fVar7 = mStrength;
        fVar5 = (g_currentTime - local_8) * mSpeed;
    } else if (local_4 == 1) {
        // mode 1: use speed multiplied by elapsed time, plus strength * something
        fVar7 = mSpeed;
        fVar5 = (g_currentTime - local_8) * mStrength;
    } else if (local_4 == 3) {
        // mode 3: random value
        fVar5 = (float) randomFloat();
        goto LAB_0082811a;
    } else {
        // other modes: skip the interpolation
        goto LAB_0082811a;
    }
    uVar3 = 1;
    fVar5 = fVar5 + fVar7 * local_8;

LAB_0082811a:
    fVar2 = g_previousTime;
    fVar7 = g_currentTime;

    if ((mLoop == 0) || (mStopFlag != 0)) {
        // non-looping or stop requested
        if (mDuration <= 0.0f) {
            mRemainingTime = 0.0f;
        } else {
            // decrease remaining time by delta time / duration (scaled)
            mRemainingTime -= (g_currentTime - mLastUpdateTime) / mDuration;
        }
    } else {
        // looping mode
        if (mDuration <= 0.0f) {
            // no duration limit -> reset to max?
            mRemainingTime = g_currentTime;
        } else {
            // increase remaining time by delta / duration (recharge)
            mRemainingTime += (g_currentTime - mLastUpdateTime) / mDuration;
        }
    }

    // clamp mRemainingTime to [0, currentTime]
    fVar1 = mRemainingTime;
    fVar6 = 0.0f;
    if (fVar1 > 0.0f) {
        fVar6 = fVar1;
        if (fVar7 <= fVar1) {
            fVar6 = fVar7;
        }
    }
    mRemainingTime = fVar6;

    // store last update time
    mLastUpdateTime = fVar2;

    // apply vibration: speed * remaining time fraction (scaled)
    applyRumble(fVar6 * fVar5);

    return uVar3;
}