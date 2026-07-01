// FUNC_NAME: WeaponCooldownManager::updateTimer

void __thiscall WeaponCooldownManager::updateTimer(float currentTime)
{
    // Offsets: 
    // +0x58: m_secondTimer (timer object for stage 2)
    // +0x60: m_secondTimerDuration (float)
    // +0x64: m_totalCooldownDuration (float) - maximum elapsed time before reset
    // +0x68: m_firstTimer (timer object for stage 1)
    // +0x70: m_firstTimerDuration (float)
    // +0x74: m_phaseThreshold (float) - time within total cooldown that triggers stage 2
    // +0x78: m_lastUpdateTime (float)
    // +0x7C: m_state (int) - 0 = idle, 1 = stage1 active, 2 = stage2 active

    float elapsed = (float)((uint)(currentTime - m_lastUpdateTime) & kTimeMask); // time since last update, wrapped if necessary
    float totalDuration = *(float *)(this + 0x64);
    float phaseThreshold = *(float *)(this + 0x74);

    if (elapsed < totalDuration || elapsed == totalDuration)
    {
        // Still within the total cooldown window
        if (elapsed <= phaseThreshold && *(int *)(this + 0x7c) != 2)
        {
            // Enter stage 2
            if (kZeroThreshold <= *(float *)(this + 0x70))
            {
                timerStart(this + 0x68, 0, *(float *)(this + 0x70), 0, 0);
            }
            else
            {
                timerStop(this + 0x68);
            }
            *(int *)(this + 0x7c) = 2;
        }
    }
    else
    {
        // The elapsed time exceeded total duration => cooldown expired
        if (*(int *)(this + 0x7c) != 1)
        {
            if (*(float *)(this + 0x60) < kZeroThreshold)
            {
                // Start stage 1 by initializing second timer? Actually this seems to reset the first timer
                timerInit(& *(uint *)(this + 0x58), 0, 0); // local variables carry m_secondTimer value
                *(int *)(this + 0x7c) = 1;
                *(float *)(this + 0x78) = currentTime;
                return;
            }
            else
            {
                timerStart(this + 0x58, 0, *(float *)(this + 0x60), 0, 0);
                *(int *)(this + 0x7c) = 1;
                *(float *)(this + 0x78) = currentTime;
                return;
            }
        }
    }
    *(float *)(this + 0x78) = currentTime;
}