// FUNC_NAME: DelayedEvent::processTick
void __fastcall DelayedEvent::processTick(DelayedEvent* this)
{
    // Check if a timed action is pending (bit 5 of flags at +0x4c)
    if (this->flags & 0x20)
    {
        // Retrieve timer info block stored at +0x20
        TimerInfo* timerInfo = (TimerInfo*)this->timerInfoPtr;

        // Decrement reference count on the timer info (keep alive during processing)
        decrementReferenceCount(timerInfo);

        if (timerInfo->refCount != 0) // still valid after release
        {
            // Decrement remaining ticks (short at +0x06)
            timerInfo->remainingTicks--;

            if (timerInfo->remainingTicks == 0)
            {
                // Fire the callback function pointer (stored at +0x00) with argument 1 (timeout)
                timerInfo->callback(1);
            }
        }

        // Clear the pending flag
        this->flags &= ~0x20;

        // Trigger global timer housekeeping (e.g., process expired timers)
        checkGlobalTimers();
    }
}