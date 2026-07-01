// FUNC_NAME: TimeOfDay::interpolateOrientation
// Function at 0x00820590: Interpolates orientation (quaternion) based on time of day.
// param_1: this pointer (TimeOfDay object with time fields at +0x10,+0x14,+0x18, quat at +0x100, matrix at +0xc0)
// param_2: start keyframe (time + quaternion at +0x100)
// param_3: end keyframe (time + quaternion at +0x100)
// Uses global constants: SECONDS_PER_DAY (0x00d73394), ROUND_CONST (0x00e44578), NORM_THRESH (0x00e44768), ONE (0x00d5780c), MASK (0x00e44680)

void __thiscall TimeOfDay::interpolateOrientation(int thisPtr, int startKey, int endKey)
{
    int startSeconds, endSeconds, thisSeconds;
    float startTime, endTime, thisTime, t;
    float *quatOut;

    // Convert start keyframe time (hour, minute, second) to total seconds
    startSeconds = *(int *)(startKey + 0x18) + 
                  (*(int *)(startKey + 0x14) + *(int *)(startKey + 0x10) * 60) * 60;
    startTime = (float)startSeconds;
    if (startSeconds < 0) {
        startTime += 0.5f; // rounding adjustment (compiler artifact)
    }

    // Convert end keyframe time to total seconds
    endSeconds = *(int *)(endKey + 0x18) + 
                (*(int *)(endKey + 0x14) + *(int *)(endKey + 0x10) * 60) * 60;
    endTime = (float)endSeconds;
    if (endSeconds < 0) {
        endTime += 0.5f;
    }

    if (endTime == startTime) {
        // No time difference: copy start orientation directly
        *(long long *)(thisPtr + 0x100) = *(long long *)(startKey + 0x100);
        *(long long *)(thisPtr + 0x108) = *(long long *)(startKey + 0x108);
        *(long long *)(thisPtr + 0x110) = *(long long *)(startKey + 0x110);
        *(long long *)(thisPtr + 0x118) = *(long long *)(startKey + 0x118);
    } else {
        // Compute interpolation factor t
        thisSeconds = *(int *)(thisPtr + 0x18) + 
                     (*(int *)(thisPtr + 0x14) + *(int *)(thisPtr + 0x10) * 60) * 60;
        thisTime = (float)thisSeconds;
        if (thisSeconds < 0) {
            thisTime += 0.5f;
        }

        if (endTime <= startTime) {
            // Wrap around midnight (endTime < startTime)
            if (thisTime < startTime) {
                t = (86400.0f - startTime + thisTime) / (86400.0f - startTime + endTime);
            } else {
                t = (thisTime - startTime) / (endTime - startTime);
            }
        } else {
            // Normal forward interpolation
            t = (thisTime - startTime) / (endTime - startTime);
        }

        // Call quaternion slerp: FUN_0056db60(t, startQuat, endQuat, outQuat)
        FUN_0056db60(t, startKey + 0x100, endKey + 0x100, thisPtr + 0x100);
    }

    // Normalize the resulting quaternion
    quatOut = (float *)(thisPtr + 0x100);
    float magSq = quatOut[0] * quatOut[0] + quatOut[1] * quatOut[1] + 
                  quatOut[2] * quatOut[2] + quatOut[3] * quatOut[3];
    // Check if magnitude is not 1.0 (with epsilon)
    if (magSq != 1.0f) {
        float invMag = 1.0f / sqrtf(magSq);
        quatOut[0] *= invMag;
        quatOut[1] *= invMag;
        quatOut[2] *= invMag;
        quatOut[3] *= invMag;
    }

    // Convert quaternion to matrix at +0xc0
    FUN_0056dc20(quatOut, thisPtr + 0xc0);
}