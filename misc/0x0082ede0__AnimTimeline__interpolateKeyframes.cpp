// FUNC_NAME: AnimTimeline::interpolateKeyframes

// 0x0082ede0: Interpolates between two keyframe nodes based on a given time-of-day.
// Takes a TimeOfDay struct (hours, minutes, seconds) and returns interpolated value
// along with indices and blend ratio.

#include <cstdint>

// Constants
const float FLOAT_BIAS = DAT_00e44578;  // 0x00e44578: floating point bias for negative conversion
const float G_CURRENT_TIME = _DAT_00d5780c;  // 0x00d5780c: global current time (float)

// TimeOfDay struct: likely year, month, day, hour, minute, second
struct TimeOfDay {
    int32_t year;
    int32_t month;
    int32_t day;
    int32_t hour;
    int32_t minute;
    int32_t second;
};

// Output structure for keyframe indices and blend ratio
struct KeyframeOutput {
    uint32_t indexA;   // [0]
    uint32_t indexB;   // [1]
    uint32_t blend;    // [2] encoded float ratio (interpret as uint)
};

// Forward declarations for helper functions
extern int32_t __fastcall findKeyframeIndex(TimeOfDay* timeStruct); // FUN_0082c3f0
extern void __fastcall logKeyframeNotFound();                        // FUN_00822f30
extern void __fastcall applyKeyframe(int32_t keyframeNode);          // FUN_008231a0
extern void __fastcall interpolateKeyframeData(                     // FUN_00823500
    float* outResult, float blend, int32_t nodeA, int32_t nodeB
);

uint32_t __thiscall AnimTimeline::interpolateKeyframes(
    this,
    uint32_t returnValue,  // param_2: returned directly (likely an interpolated value)
    TimeOfDay* timeStruct,
    KeyframeOutput* outInfo
) {
    // +0x04: current index
    // +0x08: pointer to array of keyframe node pointers
    // +0x0c: number of keyframes

    float result;       // local_120 (4 bytes)
    int32_t* keyframeArray = *(int32_t**)(this + 0x08);
    int32_t keyframeCount = *(int32_t*)(this + 0x0c);

    int32_t index = findKeyframeIndex(timeStruct);
    if (index == -1) {
        if (outInfo != nullptr) {
            outInfo->indexA = 0xffffffff;
            outInfo->indexB = 0xffffffff;
            outInfo->blend = 0;
        }
        logKeyframeNotFound();
        // Note: in this path, the function still continues to call applyKeyframe(result) at end,
        // but result is uninitialized. Ghidra suggests it may be intentional.
    } else {
        *(int32_t*)(this + 0x04) = index;
        float currentTime = G_CURRENT_TIME;

        // Determine next index (cyclic)
        int32_t nextIndex;
        if (index < keyframeCount - 1) {
            nextIndex = index + 1;
        } else {
            nextIndex = 0;
        }

        int32_t nodeA = *(int32_t*)(keyframeArray + index);
        int32_t nodeB = *(int32_t*)(keyframeArray + nextIndex);

        // Node time in seconds since midnight: hour*3600 + minute*60 + second
        // Offsets: +0x10 = hour, +0x14 = minute, +0x18 = second
        uint32_t secsA = *(int32_t*)(nodeA + 0x18) +
                         (*(int32_t*)(nodeA + 0x14) + *(int32_t*)(nodeA + 0x10) * 60) * 60;

        int32_t deltaTime;    // iVar10: time difference from nodeA to target
        int32_t interval;     // iVar8: time difference from nodeA to nodeB (wrapping if necessary)

        if (nextIndex == 0) { // wrap around midnight
            uint32_t targetSecs = timeStruct->second +
                                  (timeStruct->minute + timeStruct->hour * 60) * 60;
            // Seconds from nodeB to end of previous day + its own time
            uint32_t secsB = *(int32_t*)(nodeB + 0x18) +
                             (*(int32_t*)(nodeB + 0x14) + *(int32_t*)(nodeB + 0x10) * 60) * 60;
            interval = secsB + (86400 - secsA);  // total seconds from nodeA to nodeB across midnight

            if (targetSecs < secsA) {
                deltaTime = targetSecs + (86400 - secsA); // target is after midnight
            } else {
                deltaTime = targetSecs - secsA;
            }
        } else {
            //  (target seconds) - (nodeA seconds)
            deltaTime = ((timeStruct->minute + timeStruct->hour * 60) * 60 -
                         (int32_t)secsA) + timeStruct->second;
            interval = (*(int32_t*)(nodeB + 0x18) +
                        (*(int32_t*)(nodeB + 0x14) + *(int32_t*)(nodeB + 0x10) * 60) * 60) -
                       (int32_t)secsA;
        }

        if (interval == 0) {
            if (outInfo != nullptr) {
                outInfo->indexA = (uint32_t)index;
                outInfo->indexB = (uint32_t)nextIndex;
                outInfo->blend = (uint32_t)currentTime;  // store raw float as uint
            }
            applyKeyframe(nodeB);  // directly use nodeB
            // Note: result not set here, but later applyKeyframe(result) will use uninitialized
        } else {
            float t = (float)deltaTime;
            if (deltaTime < 0) {
                t += FLOAT_BIAS;  // bias for negative-to-float conversion
            }
            float d = (float)interval;
            if (interval < 0) {
                d += FLOAT_BIAS;
            }

            float ratio = t / d;  // blend factor

            if (outInfo != nullptr) {
                float storedBlend = currentTime - ratio;
                outInfo->indexA = (uint32_t)index;
                outInfo->indexB = (uint32_t)nextIndex;
                outInfo->blend = (uint32_t)storedBlend;
            }

            // Interpolate and store result in local float variable
            interpolateKeyframeData(&result, ratio, nodeA, nodeB);
        }

        // Copy input time struct into local variable (likely for debugging or reference)
        TimeOfDay localCopy; // represented by local_11c..local_108
        if (&localCopy != timeStruct) {
            localCopy = *timeStruct;
        }
    }

    // Apply the interpolated result (even if not set above, might be default)
    applyKeyframe(result);
    return returnValue;
}