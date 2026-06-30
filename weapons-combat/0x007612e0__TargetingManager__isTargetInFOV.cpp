// FUNC_NAME: TargetingManager::isTargetInFOV
uint __thiscall TargetingManager::isTargetInFOV(int this, float *targetObject, float *targetPosition) {
    uint result;
    float *pCurrentTarget;
    float *pTargetPosition;
    float deltaX, deltaY, deltaZ;
    float distSq;
    int playerTransform;
    float *temp;

    // Initial result from EAX (likely from a caller)
    result = in_EAX & 0xffffff00;

    // Check if the target's flags match the expected mask: this+0x1c is a flag mask,
    // targetObject+6 is a ushort flags for the target.
    if ((*(ushort *)(this + 0x1c) & *(ushort *)(targetObject + 6)) == 0) {
        // Attempt caching: if we have a stored current target position and it matches the given targetPosition,
        // and stored current target object matches given targetObject, return early with the cached pointer.
        pCurrentTarget = *(float **)(this + 0x10);
        if (pCurrentTarget != NULL && pCurrentTarget == targetPosition &&
            *(float **)(this + 0x18) == targetObject) {
            return (uint)pCurrentTarget & 0xffffff00;
        }

        // Use a different cached pointer: this+4 points to something (maybe an array of target info?)
        pCurrentTarget = *(float **)(this + 4);
        if (pCurrentTarget != NULL) {
            pCurrentTarget = pCurrentTarget + -0x12; // Adjust pointer to actual target data
            if (pCurrentTarget != NULL) {
                // Get the player's transform (position + forward vector) from some global context
                playerTransform = FUN_00471610();
                // Compute delta vector: target position relative to player position
                // targetObject is expected to contain a position at indices 0,1,2
                deltaX = targetObject[0] - *(float *)(playerTransform + 0x30);
                deltaY = targetObject[1] - *(float *)(playerTransform + 0x34);
                deltaZ = targetObject[2] - *(float *)(playerTransform + 0x38);
                temp = (float *)(playerTransform + 0x30);
                distSq = deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ;

                // Check distance thresholds
                if (distSq < DAT_00e51b38) { // very close: accept immediately
                    return (uint)pCurrentTarget & 0xffffff00;
                }
                if (distSq <= DAT_00e51b34) { // within moderate range: also check view cone
                    // Normalize the delta vector (in-place on the delta components)
                    FUN_0054ba20(&deltaX, &deltaX, 0); // likely a normalize function
                    playerTransform = FUN_00471610(); // get player transform again (or same)
                    // Player's forward direction is at playerTransform+0x20, +0x24, +0x28
                    temp = (float *)(playerTransform + 0x20);
                    // Dot product: (playerForward - ??) * deltaX + ... Actually DAT_00e44564 appears to be a constant (maybe 1.0 or 0.0)
                    // This computes something like (targetDir) dot (forward) but with adjustment by DAT_00e44564
                    float dot = (DAT_00e44564 - *(float *)(playerTransform + 0x24)) * deltaY
                              + (DAT_00e44564 - *temp) * deltaX
                              + (DAT_00e44564 - *(float *)(playerTransform + 0x28)) * deltaZ;
                    if (DAT_00d5ef54 <= dot) { // if target is sufficiently aligned in view cone, accept
                        return (uint)pCurrentTarget & 0xffffff00;
                    }
                }
            }
        }
        // If not accepted, return with low byte = 1 (indicating "invisible" or "out of range"?) and high bytes from pCurrentTarget
        result = CONCAT31((int3)((uint)pCurrentTarget >> 8), 1);
    }
    return result;
}