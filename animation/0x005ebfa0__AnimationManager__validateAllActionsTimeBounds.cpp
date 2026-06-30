// FUNC_NAME: AnimationManager::validateAllActionsTimeBounds
undefined1 AnimationManager::validateAllActionsTimeBounds(int this, int layerIndex) {
    float currentTime;
    int actionPtr;
    int frameIndex;
    uint actionCount;
    byte valid;
    uint idx;
    int keyframeBase;
    int tempBuffer[2];

    valid = 1;
    // Check required non-null pointers at +0x580 and +0x56c (likely object/resource references)
    if (*(int *)(this + 0x580) == 0 || *(int *)(this + 0x56c) == 0) {
        return 0;
    }
    if (layerIndex != 0) {
        idx = 0;
        // Lookup action set by layer ID (e.g., animation layer or effect index)
        actionPtr = lookupActionSet(layerIndex);
        if (actionPtr != 0) {
            actionCount = *(uint *)(actionPtr + 0x274); // Number of actions in this set
        }
        if (actionCount != 0) {
            do {
                actionPtr = lookupActionSet(layerIndex);
                if ((actionPtr == 0) || (*(uint *)(actionPtr + 0x274) <= idx) ||
                    (*(int *)(*(int *)(actionPtr + 0x270) + idx * 4) == 0)) {
                    // Invalid index or null action pointer
                    valid = 0;
                } else {
                    // Get action data
                    actionPtr = *(int *)(*(int *)(actionPtr + 0x270) + idx * 4); // +0x270: array of action pointers
                    currentTime = *(float *)(actionPtr + 0x60); // Action current time
                    frameIndex = *(int *)(actionPtr + 0x5c); // Action frame index (or animation ID)
                    // Check if action has valid animation data
                    actionPtr = getAnimationKeyframe(*(undefined4 *)(actionPtr + 0x54), tempBuffer);
                    if (actionPtr == 0) {
                        valid = 0;
                    } else {
                        // Enter critical section for keyframe reading
                        beginCriticalSection();
                        // Calculate address of keyframe data: base + ( frameOffset + frameIndex ) * sizeof(Keyframe)
                        // +0x18: pointer to keyframe array? +0x2d: offset per action type?
                        keyframeBase = *(int *)(tempBuffer[0] + 0x18) + 
                                      ((uint)*(byte *)(tempBuffer[0] + 0x2d) + frameIndex) * 0x28;
                        // Check if current time is within keyframe's time range (min/max)
                        if (((double)currentTime < *(double *)(keyframeBase + 0x10)) ||
                            (*(double *)(keyframeBase + 0x18) < (double)currentTime)) {
                            valid = 0;
                            endCriticalSection();
                        } else {
                            // Time is valid; apply the keyframe (e.g., set animation timing)
                            applyKeyframeAnimation(frameIndex, currentTime);
                            endCriticalSection();
                        }
                    }
                }
                idx = idx + 1;
                if (actionCount <= idx) {
                    return valid;
                }
            } while (true);
        }
    }
    return 1;
}