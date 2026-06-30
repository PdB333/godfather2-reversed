// FUNC_NAME: EventScheduler::scheduleEvent
// Function address: 0x005f0910
// Searches for an event slot with fireTime >= currentTime and smallest difference,
// marks it as scheduled (sets flag at +0x0C to 1).
// If m_bPaused (byte at +0x258) is zero and an inactive slot is found first, exits early.
// Array at +0x18: 35 entries, each 16 bytes.

void EventScheduler::scheduleEvent(int currentTime)
{
    // Event structure offset +0x18
    int *pEventBase = reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x18);
    int *bestEvent = nullptr;
    int bestDiff = 0x7fffffff;

    for (unsigned int i = 0; i < 35; i++)
    {
        int *pCandidate = bestEvent; // keep previous best

        // Check if event is inactive (byte at offset +0x08 == 0)
        if (*reinterpret_cast<char *>(pEventBase + 2) == '\0')
        {
            pCandidate = pEventBase - 1; // point to this event's struct start? (actually previous int)
            // If paused flag (+0x258) is zero, stop searching
            if (*reinterpret_cast<char *>(this + 600) == '\0')
                break;

            pCandidate = bestEvent; // revert to previously found
            // Check fire time: currentTime <= event->fireTime
            if ((currentTime <= *pEventBase) &&
                (int diff = *pEventBase - currentTime; diff < bestDiff))
            {
                pCandidate = pEventBase - 1;
                bestDiff = diff;
            }
        }

        ++i; // but loop decrement already? Actually uVar5 increments
        pEventBase += 4; // move to next event (sizeof = 16)
        bestEvent = pCandidate;
    }

    if (bestEvent != nullptr)
    {
        // Mark event as scheduled: set byte at offset +0x0C to 1
        *reinterpret_cast<char *>(bestEvent + 3) = 1;
    }
}