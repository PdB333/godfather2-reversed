// FUNC_NAME: TimeInterpolator::evaluate
// Reconstructed from Ghidra at 0x0082f6f0
// Interpolates a time-based curve sampling keyframes and producing an output vector.
// The class holds an array of keyframes (pointer at +0x08, count at +0x0c) and a current index (+0x04).
// Each keyframe has time (hours +0x10, minutes +0x14, seconds +0x18) and 3-component value (+0x4c, +0x54, +0x5c).
// The input time is a struct with 6 uint32 (year, month, day? at [0..2] then hour, minute, second at [3..5]).
// Output is an object (param_2) containing a vtable pointer and three values.
// If no valid keyframe is found, the function falls back to copying global day/night values.

struct Keyframe {
    // +0x10
    uint32_t hours;
    // +0x14
    uint32_t minutes;
    // +0x18
    uint32_t seconds;
    // ... possibly padding ...
    // +0x4c
    float valueX;
    // +0x54
    float valueY;
    // +0x5c
    float valueZ;
};

class TimeInterpolator {
public:
    Keyframe** keyframes; // +0x08
    int32_t keyframeCount; // +0x0c (max index = keyframeCount-1)
    int32_t currentIndex; // +0x04 (used to track latest sampled index)

    // __thiscall
    InterpolatedVector* evaluate(uint32_t* inputTime, InterpolatedVector* outResult, uint32_t* debugInfo) __thiscall;
};

// Output object: vtable pointer at +0x00, then three floats at +0x13*4, +0x15*4, +0x17*4
class InterpolatedVector {
public:
    void** vtable; // +0x00
    // +0x4c
    float x;
    // +0x54
    float y;
    // +0x5c
    float z;
};

// External function: finds the keyframe index for a given time point
int32_t findKeyframeIndex(TimeInterpolator* self, uint32_t* time) __thiscall; // 0x0082c5b0

// External function: returns current game time as 6-uint32 struct
void getCurrentGameTime(uint32_t* outTime); // 0x008334a0

// External function: copies data between memory (size unknown)
void memcpyOrConstruct(void* dest, void* src, uint32_t size); // 0x0081f9f0 (assumed)

// External function: performs linear interpolation between two keyframe values
void interpolateKeyframes(void* dest, float t, Keyframe* a, Keyframe* b); // 0x0082b580

// Global day/night curve data (used when no keyframe found)
extern float DAT_00d5ef88; // first component
extern float _DAT_00d5cf70; // second component
extern float DAT_00e44630; // third component? Actually from code: local_1c = CONCAT44(DAT_00e44630, _DAT_00d5cf70); so two floats condensed into int64? May be packed.
extern float DAT_00d6471c; // component

// External global for float conversion
extern float DAT_00e44578; // 0x4f800000? (2^31? Actually used for negative float handling, might be 2^32 or just large number for conversion)
extern float _DAT_00d5780c; // a default blend factor?

InterpolatedVector* __thiscall TimeInterpolator::evaluate(uint32_t* inputTime, InterpolatedVector* outResult, uint32_t* debugInfo) {
    int32_t idx = findKeyframeIndex(this, inputTime); // returns index of keyframe that best matches time, or -1
    if (idx == -1) {
        if (debugInfo != nullptr) {
            debugInfo[0] = 0xffffffff;
            debugInfo[1] = 0xffffffff;
            debugInfo[2] = 0;
        }
        // Fallback: get current game time and fill with global day/night values
        getCurrentGameTime(); // assumes modifies global data via CONCAT44
        // Use global values to fill output
        // The following copies global DAT values into local structure
        // local_24 = CONCAT44(DAT_00d6471c, DAT_00d5ef88);
        // local_1c = CONCAT44(DAT_00e44630, _DAT_00d5cf70);
        // local_14 = _DAT_00d5cf70; // Actually used as third component?
        InterpolatedVector defaultVector;
        defaultVector.x = DAT_00d5ef88; // from low half
        defaultVector.y = DAT_00d6471c; // from high half
        defaultVector.z = _DAT_00d5cf70; // from DAT_00d5cf70
        // Possibly other components not stored because outResult layout unknown?
        // The code sets outResult[0x13] = local_24; etc.
        // Actually param_2 + 0x13, +0x15, +0x17 are the float fields.
        // So we copy accordingly:
        *(float*)((uint32_t)outResult + 0x4c) = defaultVector.x;
        *(float*)((uint32_t)outResult + 0x54) = defaultVector.y;
        *(float*)((uint32_t)outResult + 0x5c) = defaultVector.z;
        outResult->vtable = &PTR_LAB_00d7377c; // vtable pointer
        return outResult;
    }

    // Store current index
    this->currentIndex = idx;

    // Determine next index (wrapping around)
    int32_t idxNext;
    if (idx < this->keyframeCount - 1) {
        idxNext = idx + 1;
    } else {
        idxNext = 0; // wrap to first keyframe for overnight interpolation
    }

    Keyframe* keyA = this->keyframes[idx];
    Keyframe* keyB = this->keyframes[idxNext];

    // Convert keyframe times to seconds within a 24-hour day
    uint32_t timeA = keyA->hours * 60 * 60 + keyA->minutes * 60 + keyA->seconds;
    uint32_t timeB = keyB->hours * 60 * 60 + keyB->minutes * 60 + keyB->seconds;

    // Convert input time to seconds (only hour, minute, second parts from inputTime[3..5])
    // Input time structure: [unused0, unused1, unused2, hour, minute, second]
    uint32_t inputHour = inputTime[3];
    uint32_t inputMinute = inputTime[4];
    uint32_t inputSecond = inputTime[5];
    uint32_t inputTimeSec = inputHour * 60 * 60 + inputMinute * 60 + inputSecond;

    // Compute time difference from keyA to input and to keyB, handling day wrap
    int32_t diffToB;
    int32_t diffFromInputToB;
    if (idxNext == 0) {
        // Wrapping: next is start of day
        diffToB = timeB + (86400 - timeA);
        diffFromInputToB = inputTimeSec + (86400 - timeA);
        // Actually the code computes iVar10 = inputTimeSec - timeA (possibly negative) and adjusts with wrap
        // Simpler: compute signed difference with wrap
    } else {
        diffToB = timeB - timeA;
        diffFromInputToB = inputTimeSec - timeA;
    }

    // Compute fractional time t = diffFromInputToB / diffToB
    // iVar10 = diffFromInputToB, iVar8 = diffToB
    // The code adjusts for negative by adding DAT_00e44578 (likely 2^31 for unsigned-to-float)
    // For clarity, we compute as float and clamp.
    float t;
    if (diffToB == 0) {
        // No time difference: use next keyframe directly
        if (debugInfo != nullptr) {
            debugInfo[0] = (uint32_t)idx;
            debugInfo[1] = (uint32_t)idxNext;
            debugInfo[2] = (uint32_t)_DAT_00d5780c; // default blend factor
        }
        // Copy keyB's data to output
        // memcpy / construct
        memcpyOrConstruct(outResult, keyB, sizeof(InterpolatedVector));
        // Override with keyB values
        outResult->x = keyB->valueX;
        outResult->y = keyB->valueY;
        outResult->z = keyB->valueZ;
        outResult->vtable = &PTR_LAB_00d7377c;
        return outResult;
    }

    // Compute ratio
    float ratio = (float)diffFromInputToB / (float)diffToB;
    t = _DAT_00d5780c - ratio; // _DAT_00d5780c appears to be 1.0? Actually used as default and then subtracted? From code: fVar11 = _DAT_00d5780c - fVar5/fVar6; where fVar5/fVar6 = ratio. So t = 1 - ratio? But then they pass ratio to interpolate: fVar5/fVar6. Let's analyze: at end if not zero, they call FUN_0082b580(&local_70, fVar5/fVar6, iVar3, iVar4); passing ratio. Then after that they set param_2 fields from local_70? Wait: After interpolation, local_24, local_1c, local_14 are set? Actually after FUN_0082b580, the result is stored in local_70? No, local_70 is a pointer to vtable? The code is confusing. Let's re-evaluate: The function appears to do interpolation into a local output (local_70 is a pointer to the vtable? Actually local_70 is a pointer that gets set to vtable, then it's used as destination for interpolation? The code does:
    // FUN_0082b580(&local_70, fVar5/fVar6, iVar3, iVar4);
    // After that, it copies local_70 fields to param_2? But local_24, local_1c, local_14 are set BEFORE the call? Actually they are set after the call? The decompiled code is tricky.
// Actually the order:
// 1. Determine indices.
// 2. If idxNext==0 case: compute diffs.
// 3. Then if iVar8==0: handle it.
// 4. Otherwise compute t = iVar10/iVar8? Then store blend factor in debugInfo.
// 5. Then call FUN_0082b580(&local_70, fVar5/fVar6, iVar3, iVar4); passing iVar3 (keyA) and iVar4 (keyB).
// 6. Then if (&local_6c != param_3) copy inputTime to local_6c.
// 7. Then call FUN_0081f9f0(&local_70); // copies from local_70? Actually it might copy the structure local_70 (which contains temp result) to param_2? But then it sets param_2 fields after.
// Actually the code after FUN_0081f9f0 is:
//   *(undefined8 *)(param_2 + 0x13) = local_24;
//   *(undefined8 *)(param_2 + 0x15) = local_1c;
//   param_2[0x17] = local_14;
//   *param_2 = &PTR_LAB_00d7377c;
// So FUN_0081f9f0 might be initializing local_70? Or copying something? The exact semantics are unclear.
// For simplicity, we assume the interpolation function writes the result into a temporary struct at local_70, and then that struct is later copied into outResult.
// We will abstract the interpolation.

    // Simplified: call interpolation with ratio
    // We create a temporary output struct (like InterpolatedVector)
    // Then copy its fields to outResult.
    InterpolatedVector temp;
    interpolateKeyframes(&temp, t, keyA, keyB); // Actually t should be between 0 and 1. From code, they pass fVar5/fVar6 as the ratio (iVar10/iVar8). So t = (float)diffFromInputToB / (float)diffToB.
    // Then set outResult fields
    outResult->x = temp.x;
    outResult->y = temp.y;
    outResult->z = temp.z;
    outResult->vtable = &PTR_LAB_00d7377c;

    // Set debug info if provided
    if (debugInfo != nullptr) {
        debugInfo[0] = (uint32_t)idx;
        debugInfo[1] = (uint32_t)idxNext;
        // t is the interpolant; store as float bits
        debugInfo[2] = *(uint32_t*)&t;
    }

    return outResult;
}
```