// FUN_00457fe0: EventManager::processTimedEvent
void EventManager::processTimedEvent()
{
    EventData* pEvent = *(EventData**)(this + 0x14); // +0x14: current event data pointer
    if (pEvent != nullptr)
    {
        int isEngineActive = FUN_00ab4db0(&DAT_00e2e4c8); // check global engine state
        if (isEngineActive)
        {
            if (pEvent->state != 2) // 2 = eState_Waiting?
            {
                pEvent->state = 4; // 4 = eState_Completed
                uint64_t currentTime = FUN_00ac28e0(); // get current game timestamp
                // If timestamp changed since last recorded, reset lastTime
                if (currentTime != *(uint64_t*)(&pEvent->lastTime)) // +0x1d8/+0x1dc
                {
                    pEvent->lastTime = 0; // clear 64-bit value
                }
                FUN_00457ca0(); // cancel any pending operation
            }
            // Register a callback with the event’s callback ID (timer)
            FUN_00ac3b80(pEvent->callbackId, &EventManager::onTimedEventComplete, pEvent, 0);
            FUN_00ab4e70(); // yield/schedule next update
        }
    }
}