// FUNC_NAME: CombatKnowledge::evaluateTargetSwitch
void __thiscall CombatKnowledge::evaluateTargetSwitch(int* thisPtr, int newTargetId)
{
    // Local copies of a global constant (likely some threshold)
    float minTime = DAT_00e44794;   // +0x0? Global minimum time
    float maxTime = DAT_00e44794;   // Same constant initially

    // Virtual call to a random number generator (vtable+0x1b8)
    // Returns a 80-bit float, then multiplied by a global time scale
    float10 randomVal = (**(code (__thiscall**)(int*))(*thisPtr + 0x1b8))();
    float scaledRandom = (float)(randomVal * (float10)DAT_00d5ef70); // Time‑scaled random offset

    // FUN_00864c80 likely checks if time has elapsed since last evaluation
    char timeCheckResult = FUN_00864c80(&minTime, &maxTime);
    if (timeCheckResult != '\0') {
        if (minTime <= maxTime) {
            // Expand the window forward
            maxTime = scaledRandom * _DAT_00d5c458 + maxTime;
        } else {
            // Move window backward
            maxTime = minTime - scaledRandom;
        }

        // If the new window is still within a hard‑coded maximum, exit early
        if (maxTime <= DAT_00e540e4) {
            return;
        }
    }

    // Strip sign from current target ID (offset +0x3F5)
    uint absTargetId = thisPtr[0x3f5] & 0x7fffffff;

    // Check if there is already a pending target (offset +0x3F4) that is nearly reached
    if ((thisPtr[0x3f4] < (int)(absTargetId - 1)) || (thisPtr[0x3f5] < 0)) {
        float distanceThreshold = scaledRandom * DAT_00d5eee4;

        // FUN_00865780 likely checks if the new target is within this distance
        char distanceCheck = FUN_00865780(absTargetId, &distanceThreshold);
        if ((distanceCheck != '\0') && (distanceThreshold < scaledRandom * DAT_00e445a4)) {
            return; // Target is too close, skip switch
        }
    }

    // Commit to the new target
    thisPtr[0x402] = newTargetId;               // +0x1008: New target ID
    thisPtr[0x3da] = 0;                         // +0xF68: Reset target state
    thisPtr[0x3d7] = 0;                         // +0xF5C: Reset another state
    thisPtr[0x3de] = 0;                         // +0xF78: Reset another state
    thisPtr[0x3ca] = thisPtr[0x3ca] | 0x10000000; // +0xF28: Set "target acquired" flag

    // Update target timer
    float timerBase = DAT_00e44564;
    if (thisPtr[0x3f5] < 0) {
        timerBase = DAT_00d5ef70;
    }
    thisPtr[0x3f2] = (int)((float)(absTargetId) * DAT_00d75750 + timerBase); // +0xFC8: New timer value
}