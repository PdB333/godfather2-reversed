// FUNC_NAME: TimerManager::updateTimer
// Address: 0x0093e520
// Called when a timer event occurs: if the timer matches the current timer, update its state and reset fields.
// If not, clean up the timer and decrement count.

void __thiscall TimerManager::updateTimer(TimerObject* timer, bool start)
{
    uint newTime;

    // +0x78: pointer to current active timer
    if (timer == this->currentTimer) {
        if (start) {
            // Start: set timer value to game base time, mark running
            this->currentTime = g_gameTimeBase;  // DAT_01205224
            timer->flags = 1;                    // +0x1c: timer running flag
        } else {
            // Stop: clamp timer value to max (base + 2500ms) or keep current if smaller
            newTime = g_gameTimeBase + 2500;     // 0x9c4 = 2500 ms
            if (this->currentTime < newTime) {
                newTime = this->currentTime;
            }
            this->currentTime = newTime;
            timer->flags = 0;                    // clear running flag
        }
        // Update the timer's stored value
        timer->timerValue = this->currentTime;   // +0x0c: timer value

        // Reset all other timer-related state in this manager
        this->shortField1 = 0;                   // +0x60
        this->shortField2 = 0;                   // +0x62
        this->timeField4 = 0;                    // +0x74
        this->timeField3 = 0;                    // +0x70
        this->timeField2 = 0;                    // +0x6c
        this->timeField1 = 0;                    // +0x68
        this->timeField0 = 0;                    // +0x64 (100 decimal)
    } else {
        // Not our timer: destroy and remove it
        FUN_0093e450(timer);                     // destroy timer
        FUN_0093dc20(timer);                     // remove from list
        this->timerCount--;                      // +0x50: decrement count
    }

    // If no pending flag (off +0x48) and global flag bit 0 is set, clear it
    if (this->someFlag == 0 && (this->managerFlags & 1) != 0) {
        FUN_004086d0(&g_globalTimerFlag);        // DAT_012069c4 – clear global timer flag
        this->managerFlags &= 0xFFFE;            // +0x5c: clear bit 0
    }
}