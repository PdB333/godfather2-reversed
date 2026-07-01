// FUNC_NAME: EventScheduler::scheduleNextEvent

void EventScheduler::scheduleNextEvent()
{
    Event* currentEvent = reinterpret_cast<Event*>(this->m_pCurrentEvent); // +0x8
    if (currentEvent != nullptr)
    {
        if ((currentEvent->m_flags & 1) != 0) // +0x10
        {
            currentEvent->m_flags &= 0xFFFE; // clear active flag
        }
        this->m_pCurrentEvent = nullptr; // +0x8
    }

    TimerData* timerData = reinterpret_cast<TimerData*>(this->m_pTimerData); // +0x10
    if (timerData != nullptr)
    {
        timerData->field0 = 0; // +0x0
        timerData->field1 = 0; // +0x4

        uint32_t index = g_randomMask & g_randomCounter; // DAT_010c2678 & DAT_012054b4
        g_randomCounter++; // DAT_012054b4

        // DAT_010c2680 is array of floats; DAT_0112bb50 is pointer to TimeManager
        timerData->remainingTime = g_randomFloats[index] * g_timeManager->timeScale + g_timeManager->currentTime; // +0x8
    }
}