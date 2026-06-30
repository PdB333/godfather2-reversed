// FUNC_NAME: EventScheduler::updateEventList

void __thiscall EventScheduler::updateEventList(float currentTime)
{
    uint validCount = 0; // uVar1, tracks number of valid events still in the future

    if (m_eventCount != 0) // offset +0x2c
    {
        int byteOffset = 0; // iVar2, byte offset into event array

        // Loop as long as current time is within the trigger time (+ tolerance) for this event
        while (currentTime <= (m_pEvents[byteOffset / 0xc].triggerTime + g_timeTolerance))
        {
            // Check if event slot is invalid (id == 0)
            if (m_pEvents[byteOffset / 0xc].eventId == 0)
            {
                // Remove the invalid event at the current validCount position
                // This effectively shifts the array and reduces count
                removeEvent(validCount);
            }
            else
            {
                // Valid event – count it and advance to next slot
                validCount++;
                byteOffset += 0xc;
            }

            // If we have processed all events, return
            if (m_eventCount <= validCount)
                return;
        }

        // The loop exited because we hit an event whose trigger time is in the past
        // Trim the event list to keep only the first validCount entries (still future)
        truncateEventList(validCount, m_eventCount);
    }
}