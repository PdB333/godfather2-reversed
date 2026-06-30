// FUNC_NAME: Timer::setTimer
void __thiscall Timer::setTimer(float duration, const char* name) {
    // Check if timer is already active and has a name
    if ((this->time != 0 || this->something != 0) && this->name[0] != '\0') {
        // Reset timer and stop any pending callback
        this->time = 0;
        this->something = 0;
        this->stopTimer(); // FUN_005c14a0
    }

    // Copy timer name (max 32 chars)
    strncpy(this->name, name, 32);

    // Apply time scale factor
    duration = duration * g_timeScale; // DAT_00e2e230

    // Get base time (possibly negative adjustment)
    float baseTime = (float)g_baseTime; // DAT_01205210
    if (g_baseTime < 0) {
        baseTime += (float)g_timeAdjustment; // DAT_00e44578
    }

    // Store end time as integer (rounded)
    this->something = 0;
    this->time = (int)(baseTime + duration + 0.5f); // ROUND

    // Set callback for timer expiry
    this->setTimerCallback(this + 4, &LAB_005bf950, 0); // FUN_005c0d50
}