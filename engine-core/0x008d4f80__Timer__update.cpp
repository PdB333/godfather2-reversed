// FUNC_NAME: Timer::update

void __thiscall Timer::update(float deltaTime)
{
    float timeScale = g_fTimeScale; // _DAT_00d577a0

    if (m_bIsDurationMode == 0) // +0x80
    {
        // Cooldown mode: accumulate time until cooldown duration is reached, then reset
        if ((m_fCurrentTime > 0.0f) && (m_fCooldownDuration > 0.0f)) // +0x84, +0x7c
        {
            m_fCurrentTime += deltaTime;
            if (m_fCurrentTime > m_fCooldownDuration)
            {
                m_fCurrentTime = 0.0f;
            }
        }
    }
    else
    {
        // Duration mode: accumulate time until max duration is reached, then trigger callback
        m_fCurrentTime += deltaTime;
        if ((timeScale < m_fMaxDuration) && (m_fMaxDuration < m_fCurrentTime)) // +0x78
        {
            onTimerExpired(); // FUN_008d4e80
            m_fCurrentTime = m_fCurrentTime; // redundant store, kept for accuracy
        }
    }
}