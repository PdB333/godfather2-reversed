// FUNC_NAME: TimeInterpolator::update
void TimeInterpolator::update() {
    // Query minimum timer period and set high-resolution timer
    TIMECAPS timeCaps;
    timeGetDevCaps(&timeCaps, sizeof(timeCaps));
    timeBeginPeriod(timeCaps.wPeriodMin);
    DWORD currentTime = timeGetTime();
    timeEndPeriod(timeCaps.wPeriodMin);

    // Check for timer wrap (unsigned overflow)
    if (currentTime < this->m_targetTime) {
        // Calculate elapsed time since m_startTime, handling wrap
        int elapsed = currentTime - this->m_startTime;
        float fElapsed = static_cast<float>(elapsed);
        if (elapsed < 0) {
            fElapsed += 4294967296.0f; // 2^32
        }

        // Calculate total duration between start and target times
        int duration = this->m_targetTime - this->m_startTime;
        float fDuration = static_cast<float>(duration);
        if (duration < 0) {
            fDuration += 4294967296.0f;
        }

        float fraction = fElapsed / fDuration;

        // Interpolate each value if target differs from current
        if (this->m_target0 != this->m_value0) {
            this->m_value0 = (this->m_target0 - this->m_value0) * fraction + this->m_value0;
        }
        if (this->m_target2 != this->m_value2) {
            this->m_value2 = (this->m_target2 - this->m_value2) * fraction + this->m_value2;
        }
        if (this->m_target1 != this->m_value1) {
            this->m_value1 = (this->m_target1 - this->m_value1) * fraction + this->m_value1;
        }
        if (this->m_target3 != this->m_value3) {
            this->m_value3 = (this->m_target3 - this->m_value3) * fraction + this->m_value3;
        }
        if (this->m_target4 != this->m_value4) {
            this->m_value4 = (this->m_target4 - this->m_value4) * fraction + this->m_value4;
        }
        if (this->m_targetValue != this->m_currentValue) {
            this->m_currentValue = (this->m_targetValue - this->m_currentValue) * fraction + this->m_currentValue;
        }
    } else {
        // Timer not wrapped: snap all values to their targets
        FUN_004086d0(&gTimerManager); // called at 0x004086d0
        this->m_value0 = this->m_target0;
        this->m_value1 = this->m_target1;
        this->m_value2 = this->m_target2;
        this->m_value3 = this->m_target3;
        // Note: m_value4 (at +0xa8) is intentionally not snapped?
        this->m_currentValue = this->m_targetValue;
    }

    this->m_startTime = currentTime;

    // Call through vtable of a global object (e.g., some update manager)
    // gGlobalManager points to a vtable; offset 0xbc is a method pointer
    void (*setTimerValue)(void*, float) = (void (*)(void*, float))((*(int**)DAT_01223510))[0xBC / 4];
    setTimerValue(static_cast<char*>(this) + 0x94, this->m_currentValue);
}