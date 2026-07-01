// FUNC_NAME: AnimationTrack::interpolateKeyframes

#include <cstdint>

// Represents a keyframe in an animation track
struct Keyframe {
    int field_0x00;          // +0x00: unknown
    int field_0x04;          // +0x04: unknown
    int field_0x08;          // +0x08: unknown
    int field_0x0C;          // +0x0C: unknown
    int hours;               // +0x10: hours (used in time calculation)
    int minutes;             // +0x14: minutes
    int seconds;             // +0x18: seconds
    int field_0x1C;          // +0x1C: unknown
    int field_0x20;          // +0x20: unknown
    // ... possibly more fields
    float rotationX;         // +0x4C: part of quaternion/rotation
    float rotationY;         // +0x50
    float rotationZ;         // +0x54
    float rotationW;         // +0x58
};

// Input time structure (probably a date/time with only hour/min/sec used)
struct TimeInput {
    int field_0x00; // +0x00: year? day?
    int field_0x04; // +0x04: month?
    int field_0x08; // +0x08: day?
    int hours;      // +0x0C: hours
    int minutes;    // +0x10: minutes
    int seconds;    // +0x14: seconds
};

// Output data structure (contains interpolated rotation)
struct InterpolatedOutput {
    uint32_t *vtable; // +0x00: pointer to vtable (PTR_LAB_00d73688)
    // ... up to 0x13
    float rotationX;  // +0x4C (0x13 * 4)
    float rotationY;  // +0x50
    float rotationZ;  // +0x54
    float rotationW;  // +0x58
};

// Result info when interpolating (optional)
struct InterpResultInfo {
    int keyframeA;   // index of first keyframe
    int keyframeB;   // index of second keyframe
    float ratio;     // interpolation ratio (0-1)
};

// External functions (forward declarations)
int getKeyframeIndex(const TimeInput* time);                    // FUN_0082de40
void logErrorAndAbort();                                       // FUN_008334a0 + FUN_009d3650
void assignOutputPointer(InterpolatedOutput* out, uint32_t* ptr);// FUN_0081f9f0
void interpolateKeyframesTwo(void* out, float ratio, const Keyframe* a, const Keyframe* b); // FUN_0082dba0

// Global data
extern uint32_t PTR_LAB_00d73688;   // some static vtable or constant
extern float _DAT_00d5780c;         // probably 1.0f or time scale
extern double DAT_00e44578;         // used for negative floating conversion

InterpolatedOutput* AnimationTrack::interpolateKeyframes(
    InterpolatedOutput* outData,
    const TimeInput* inTime,
    InterpResultInfo* outInfo // optional
) {
    int currentIndex = getKeyframeIndex(inTime);
    if (currentIndex == -1) {
        if (outInfo != nullptr) {
            outInfo->keyframeA = 0xFFFFFFFF;
            outInfo->keyframeB = 0xFFFFFFFF;
            outInfo->ratio = 0.0f;
        }
        logErrorAndAbort();
        // local_70 = &PTR_LAB_00d73688; // not needed in clean version
    } else {
        this->currentIndex = currentIndex;
        float ratio = _DAT_00d5780c; // default ratio (probably 1.0)
        int nextIndex = (currentIndex < this->keyframeCount - 1) ? currentIndex + 1 : 0;

        const Keyframe* keyA = this->keyframes[currentIndex];
        const Keyframe* keyB = this->keyframes[nextIndex];

        // Convert keyframe times to total seconds
        int timeA = keyA->hours * 3600 + keyA->minutes * 60 + keyA->seconds;
        int timeB = keyB->hours * 3600 + keyB->minutes * 60 + keyB->seconds;

        // Convert input time to total seconds
        int inputTime = inTime->hours * 3600 + inTime->minutes * 60 + inTime->seconds;

        int diffToNext;
        int diffInputToA;
        if (nextIndex == 0) {
            // Wrapped around: need to handle day boundary
            int daySeconds = 24 * 3600; // 86400
            diffToNext = timeB + (daySeconds - timeA); // time from A to B across day boundary
            if (inputTime < timeA) {
                diffInputToA = inputTime + (daySeconds - timeA);
            } else {
                diffInputToA = inputTime - timeA;
            }
        } else {
            diffToNext = timeB - timeA;
            diffInputToA = inputTime - timeA;
        }

        if (diffToNext == 0) {
            // Both keyframes have same time: just copy from B
            if (outInfo != nullptr) {
                outInfo->keyframeA = currentIndex;
                outInfo->keyframeB = nextIndex;
                outInfo->ratio = _DAT_00d5780c; // probably 1.0
            }
            // Copy rotation from keyframe B
            outData->rotationX = keyB->rotationX;
            outData->rotationY = keyB->rotationY;
            outData->rotationZ = keyB->rotationZ;
            outData->rotationW = keyB->rotationW;
        } else {
            // Calculate interpolation ratio
            float ratioInput = static_cast<float>(diffInputToA);
            if (diffInputToA < 0) ratioInput += static_cast<float>(DAT_00e44578);
            float ratioNext = static_cast<float>(diffToNext);
            if (diffToNext < 0) ratioNext += static_cast<float>(DAT_00e44578);
            float interpRatio = ratioInput / ratioNext;
            if (outInfo != nullptr) {
                outInfo->keyframeA = currentIndex;
                outInfo->keyframeB = nextIndex;
                outInfo->ratio = _DAT_00d5780c - interpRatio; // maybe inverted
            }
            interpolateKeyframesTwo(&outData, interpRatio, keyA, keyB);
        }

        // Copy input time fields to local? (not sure why this block exists)
        // The decompiled showed copying param_3 to local_6c... We'll skip as it's likely a bug or leftover.
    }

    assignOutputPointer(outData, &PTR_LAB_00d73688);
    // Note: local_24 etc are placed into outData at offsets 0x13-0x16
    // Actually those have been already set above (rotation). The function returns outData.
    return outData;
}