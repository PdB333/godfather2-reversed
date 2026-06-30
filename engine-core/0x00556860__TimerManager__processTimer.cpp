// FUNC_NAME: TimerManager::processTimer
void __thiscall TimerManager::processTimer(void) {
    // +0x40: pointer to a timer structure (TimerData*)
    TimerData* timer = *(TimerData**)(this + 0x40);
    if (timer != nullptr) {
        // Call a helper that might update or validate the timer
        onTimerExpired(); // FUN_00557020

        // Check if the timer has a valid callback (short at +2 non-zero)
        if (timer->callbackCount != 0) {
            // Decrement the remaining count (short at +6)
            timer->remainingCount--;
            if (timer->remainingCount == 0) {
                // Invoke the callback with argument 1
                timer->callback(1);
            }
        }
        // Clear the timer pointer
        *(TimerData**)(this + 0x40) = nullptr;
    }
}