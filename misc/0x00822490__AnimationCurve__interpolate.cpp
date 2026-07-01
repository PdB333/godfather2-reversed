// FUNC_NAME: AnimationCurve::interpolate
undefined4 AnimationCurve::interpolate(int this, undefined4 param_2, uint* inputTime, uint* outputIndices) {
    uint uVar1;
    uint nextIndex;
    int key1Data, key2Data;
    float fraction;
    int timeDiff, interval;
    int elapsedInput, elapsedKey1, elapsedKey2;
    float floatDiff, floatInterval;
    uint tempLocal[6]; // local_13c to local_128

    // Locate the keyframe index for the input time
    // inputTime is likely a pointer to a TimeOfDay struct: [?, ?, ?, hours, minutes, seconds]
    currentIndex = findKeyframeIndex(inputTime); // FUN_00821ca0
    if (currentIndex == 0xffffffff) {
        if (outputIndices != (uint*)0x0) {
            *outputIndices = 0xffffffff;
            *(outputIndices + 1) = 0xffffffff;
            *(outputIndices + 2) = 0;
        }
        resetInterpolation(); // FUN_008208c0
        return param_2; // early exit
    }

    *(uint*)(this + 4) = currentIndex; // store current keyframe index

    // Determine next keyframe index (wrap around)
    if (currentIndex < *(int*)(this + 0xc) - 1) {
        nextIndex = currentIndex + 1;
    } else {
        nextIndex = 0;
    }

    // Get pointers to keyframes from the array at this+0x8
    key1Data = *(int*)(*(int*)(this + 8) + currentIndex * 4); // keyframe struct pointer
    key2Data = *(int*)(*(int*)(this + 8) + nextIndex * 4);

    // Convert key1 time to total seconds
    // keyframe struct offsets: +0x10 = hours, +0x14 = minutes, +0x18 = seconds
    elapsedKey1 = *(int*)(key1Data + 0x18) + (*(int*)(key1Data + 0x14) + *(int*)(key1Data + 0x10) * 60) * 60;

    if (nextIndex == 0) {
        // Wrap-around case: compute interval across midnight
        // inputTime[3]=hours, inputTime[4]=minutes, inputTime[5]=seconds
        elapsedInput = inputTime[5] + (inputTime[4] + inputTime[3] * 60) * 60;
        // elapsedKey2 is for keyframe 0 (wrap) – compute total seconds
        elapsedKey2 = *(int*)(key2Data + 0x18) + (*(int*)(key2Data + 0x14) + *(int*)(key2Data + 0x10) * 60) * 60;
        // Interval is from key1 to key2 across the 24h boundary
        interval = elapsedKey2 + (86400 - elapsedKey1); // 86400 = 24*3600
        if (elapsedInput < elapsedKey1) {
            timeDiff = elapsedInput + (86400 - elapsedKey1);
        } else {
            timeDiff = elapsedInput - elapsedKey1;
        }
    } else {
        // No wrap: compute normal interval
        // timeDiff = input time - key1 time
        timeDiff = ((inputTime[4] + inputTime[3] * 60) * 60 - elapsedKey1) + inputTime[5];
        // interval = key2 time - key1 time
        interval = (*(int*)(key2Data + 0x18) + (*(int*)(key2Data + 0x14) + *(int*)(key2Data + 0x10) * 60) * 60) - elapsedKey1;
    }

    if (interval == 0) {
        // No time span between keys – use key1 directly
        if (outputIndices != (uint*)0x0) {
            *outputIndices = currentIndex;
            *(outputIndices + 1) = nextIndex;
            *(outputIndices + 2) = (uint)globalFraction; // _DAT_00d5780c (probably always 1.0)
        }
        applyKeyframe(key2Data); // FUN_00820d40 – apply key2 directly
    } else {
        // Compute interpolation fraction
        floatDiff = (float)timeDiff;
        if (timeDiff < 0) {
            floatDiff += DAT_00e44578; // constant to make positive? (2^32?)
        }
        floatInterval = (float)interval;
        if (interval < 0) {
            floatInterval += DAT_00e44578; // same constant
        }
        fraction = floatDiff / floatInterval;
        if (outputIndices != (uint*)0x0) {
            // globalFraction minus fraction? (might be >= 1.0 for normalized time)
            *outputIndices = currentIndex;
            *(outputIndices + 1) = nextIndex;
            *(outputIndices + 2) = (uint)(globalFraction - fraction);
        }
        // Interpolate between key1 and key2
        lerpKeyframes((undefined1*)&tempLocal, fraction, key1Data, key2Data); // FUN_00820e30
    }

    // Copy inputTime to tempLocal (unclear purpose, maybe for later use)
    if (&tempLocal[1] != inputTime) { // address compare – avoid self-copy
        tempLocal[0] = *inputTime;
        tempLocal[1] = inputTime[1];
        tempLocal[2] = inputTime[2];
        tempLocal[3] = inputTime[3];
        tempLocal[4] = inputTime[4];
        tempLocal[5] = inputTime[5];
    }

    // Apply interpolated keyframe (if any) and finalize
    applyKeyframe((int)&tempLocal); // FUN_00820d40
    finalizeInterpolation(); // FUN_00820940
    return param_2;
}