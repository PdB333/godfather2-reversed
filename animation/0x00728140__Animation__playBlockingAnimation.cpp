// FUNC_NAME: Animation::playBlockingAnimation
void __thiscall Animation::playBlockingAnimation(unsigned int animationHash) {
    char isFinished;
    int handleOrPointer;
    float timeDelta;

    // Initialize animation system for this animation
    initAnimation(animationHash);
    // Start playing the animation identified by hash
    startAnimation(animationHash, 0x68396409); // Hash likely for "someAnim"

    // Poll until animation completes
    isFinished = checkAnimationFinished();
    while (isFinished == 0) {
        // Advance animation state
        updateAnimation();

        // Attempt to get a handle (possibly pointer to current frame data)
        handleOrPointer = getAnimationHandle();
        if (handleOrPointer == 0) {
            // Retry getting handle and compute time delta
            handleOrPointer = updateAnimation(); // Note: second call might return different value
            timeDelta = g_globalGameTime - *(float *)(handleOrPointer + 8);
            // Store current time and delta into this object
            *(float *)(this + 0x14c) = *(float *)(handleOrPointer + 8); // +0x14c: lastSyncTime
            *(float *)(this + 0x148) = timeDelta; // +0x148: elapsedSinceSync
        }

        // End update cycle
        endAnimationUpdate();

        // Re-check completion status
        isFinished = checkAnimationFinished();
    }
}