// FUNC_NAME: Timer::tick
// Address: 0x0054e2e0
// Role: Decrements timer countdown and fires callback when expired. Part of EA EARS timer system.
// Structure at this+0x10: TimerData { void (*callback)(int); short enabled; short remainingCount; }

void Timer::tick() {
    // Get timer data block stored at offset 0x10 in this object
    TimerData* timerData = *(TimerData**)(this + 0x10);

    // If timer is enabled, decrement countdown and check for expiry
    if (timerData->enabled != 0) {
        timerData->remainingCount--;
        if (timerData->remainingCount == 0) {
            // Fire callback with argument 1 (likely timer ID or completion signal)
            timerData->callback(1);
        }
    }

    // Call to engine-level timer update (likely updates the timer system state)
    someEngineTickUpdate();  // FUN_009f01a0
}