// FUN_NAME: TimeManager::getScaledFrameTime
long double __fastcall TimeManager::getScaledFrameTime(int thisPtr) {
    double frameTime;

    // Offset +0xA0: likely a flag indicating whether time scaling is active (e.g., not paused)
    if (*(int *)(thisPtr + 0xA0) != 0) {
        // Start precise timing interval
        beginFrameTime();

        // Get the current frame time (mode 0 = absolute or unscaled)
        getFrameTime(0, &frameTime);

        // End timing interval
        endFrameTime();

        // Apply a global time scale multiplier (e.g., 1.0 / TARGET_FPS)
        return (long double)frameTime * gTimeScaleFactor;
    }

    // Return a default delta when time is not active (e.g., 0.0 or fixed dt)
    return gDefaultFrameTime;
}