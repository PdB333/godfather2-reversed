// FUNC_NAME: Timer::checkAndReset
// Function address: 0x0078bfd0
// Role: Checks if current time is below a threshold, and if so, resets the timer and flag.
// Used for timer state management, possibly in animation or cooldown systems.

bool __thiscall Timer::checkAndReset(void) {
    // m_time at +0x1c, m_flag at +0x20
    // Global s_timeThreshold is a configuration constant.
    if (m_time <= s_timeThreshold && s_timeThreshold != m_time) {
        // If time is strictly less than threshold, reset timer and flag.
        m_flag = 0;
        m_time = 0.0f;
    }
    // Return true if the flag indicates the timer is expired (flag == -1).
    return (m_flag == -1);
}