// FUNC_NAME: TimeInterpolator::calculateTimeInterpolation

// Function address: 0x0082e330
// This function takes an input time (e.g., time of day) and a list of keyframe times,
// finds the segment containing the input time, computes an interpolation factor (0..1),
// and interpolates the associated keyframe data.
// param_1 (this): pointer to TimeInterpolator object
// param_2: return value (passed through, possibly a copy of input structure)
// param_3: pointer to input time structure (6 DWORDs: unknown[0..2], hour[3], minute[4], second[5])
// param_4: optional output buffer for segment indices and interpolation factor (3 DWORDs: indexA, indexB, t)
// Returns: param_2

struct TimeOfDay {
    uint32_t hour;   // offset +0x10 from keyframe pointer? Not directly.
    uint32_t minute;
    uint32_t second;
};

// Keyframe structure: time stored at offsets 0x10, 0x14, 0x18
struct Keyframe {
    // offset 0x00: other data (not used here)
    // ...
    uint32_t hour;     // +0x10
    uint32_t minute;   // +0x14
    uint32_t second;   // +0x18
};

// Output structure for interpolation results (used by FUN_0082a4f0)
struct InterpolationResult {
    // 24 bytes total, but we only know it's passed to FUN_0082a4f0
    uint32_t data[6];
};

uint32_t __thiscall TimeInterpolator::calculateTimeInterpolation(
    int thisPtr,
    uint32_t returnVal,
    uint32_t* inputTime,     // param_3
    uint32_t* outputIndices  // param_4, optional
) {
    // Find segment index for given input time
    uint32_t idx = FUN_0082c1b0(inputTime);  // findSegmentIndex?

    if (idx == 0xFFFFFFFF) {
        // Time not found or invalid
        if (outputIndices != nullptr) {
            outputIndices[0] = 0xFFFFFFFF;
            outputIndices[1] = 0xFFFFFFFF;
            outputIndices[2] = 0;
        }
        FUN_008297a0(); // Log error or something
    } else {
        // Store current index
        *(uint32_t*)(thisPtr + 4) = idx;

        uint32_t nextIdx;
        if (idx < *(int*)(thisPtr + 0xC) - 1) {
            nextIdx = idx + 1;
        } else {
            nextIdx = 0; // wrap around
        }

        // Get pointers to current and next keyframe
        int keyframeA = *(int*)(*(int*)(thisPtr + 8) + idx * 4);
        int keyframeB = *(int*)(*(int*)(thisPtr + 8) + nextIdx * 4);

        // Convert keyframe times to total seconds from midnight
        uint32_t totalSecondsA = *(int*)(keyframeA + 0x18)  // seconds
                    + ( *(int*)(keyframeA + 0x14)  // minutes
                        + *(int*)(keyframeA + 0x10) * 60 ) * 60; // hours * 3600 + minutes*60 + seconds

        uint32_t totalSecondsB, deltaSeconds, elapsedSeconds;
        if (nextIdx == 0) {
            // Wrapping case: next is first keyframe (next day)
            // Calculate input time in seconds, possibly wrapping
            uint32_t inputTotal = inputTime[5]  // seconds
                        + ( inputTime[4]       // minutes
                            + inputTime[3] * 60 ) * 60;
            // Add a full day to keyframeB's time if needed
            totalSecondsB = *(int*)(keyframeB + 0x18)
                + ( *(int*)(keyframeB + 0x14) + *(int*)(keyframeB + 0x10) * 60 ) * 60
                + 86400; // 0x15180 seconds in a day
            if (inputTotal < totalSecondsA) {
                elapsedSeconds = inputTotal + (86400 - totalSecondsA);
            } else {
                elapsedSeconds = inputTotal - totalSecondsA;
            }
        } else {
            // Normal case: both keyframes within same day
            totalSecondsB = *(int*)(keyframeB + 0x18)
                + ( *(int*)(keyframeB + 0x14) + *(int*)(keyframeB + 0x10) * 60 ) * 60;
            elapsedSeconds = (inputTime[4] + inputTime[3] * 60) * 60 + inputTime[5] - totalSecondsA;
            // Note: this is approximate, actual code has more precise calculation.
        }

        if (totalSecondsB - totalSecondsA == 0) {
            // Zero-length segment: use default factor
            if (outputIndices != nullptr) {
                outputIndices[0] = idx;
                outputIndices[1] = nextIdx;
                outputIndices[2] = *(uint32_t*)0x00d5780c; // default t? (likely 0.0f)
            }
            FUN_0081fac0(keyframeB); // process next keyframe directly?
        } else {
            // Compute interpolation factor
            float t = (float)elapsedSeconds / (float)(totalSecondsB - totalSecondsA);
            if (outputIndices != nullptr) {
                float defaultT = *(float*)0x00d5780c;
                outputIndices[0] = idx;
                outputIndices[1] = nextIdx;
                outputIndices[2] = *(uint32_t*)&(defaultT - t); // invert? Actually code does: fVar11 = _DAT_00d5780c - fVar5 / fVar6
            }
            // Call interpolation function on the two keyframes
            InterpolationResult result;
            FUN_0082a4f0(&result, t, keyframeA, keyframeB);
        }

        // Copy input time into local variables? (likely for return or later use)
        // The actual code copies param_3[0..5] into separate locals, but we ignore that.
    }

    FUN_0081fac0(&local_c0); // unused? Might be cleanup
    return returnVal;
}