// FUNC_NAME: SimpleTimer::update

/**
 * Function address: 0x008cc1a0
 * Role: Updates an elapsed time counter against a threshold, triggers callback when threshold reached.
 * Class offsets:
 *   +0x34: float m_duration (threshold)
 *   +0x38: float m_elapsed (accumulated time)
 *   +0x3c: uint8 m_isActive (boolean flag)
 *
 * Called function: 0x00415200 (likely a callback, e.g., onTimerExpire)
 */
void __thiscall SimpleTimer::update(void)
{
    float fDelta = DAT_012067e8; // global frame delta time

    if (m_isActive != 0)
    {
        m_elapsed += fDelta;
        if (m_duration <= m_elapsed)
        {
            onTimerExpire(); // FUN_00415200
            m_isActive = 0;
        }
    }
}