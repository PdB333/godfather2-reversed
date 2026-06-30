// FUNC_NAME: Entity::updateActivationTimer
// Address: 0x006badb0
// This function manages a timer based on an activation value. When the value is non-zero and the timer is not already active,
// it starts the timer (duration 0x32 = 50). When the value becomes zero and the timer is active, it stops the timer.

void __thiscall Entity::updateActivationTimer(void)
{
    // m_activateValue at +0xA4 (int)
    // m_flags at +0x84 (uint)
    // m_timer at +0x80 (timer handle/struct)
    if (m_activateValue != 0) {
        // Check if timer is already active (bit 29 of flags)
        if ((m_flags >> 0x1d & 1) == 0) {
            // Set timer active flag
            m_flags = m_flags | 0x20000000;
            // Start timer with duration 50 (0x32)
            Timer::start(&m_timer, 50);
            return;
        }
        // Timer already active, do nothing
        return;
    }
    // Activation value is zero
    if ((m_flags >> 0x1d & 1) != 0) {
        // Stop timer
        Timer::stop(&m_timer);
        // Clear timer active flag (clear bit 29)
        m_flags = m_flags & 0xdfffffff;
    }
    return;
}