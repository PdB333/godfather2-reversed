// FUNC_NAME: TimerEvent::update
// Address: 0x0054e2e0
// Role: Decrements a countdown timer and invokes a callback upon expiration.
// Called from multiple update loops (0x008079c0, 0x007f4690, 0x007f4740).

// Structure pointed to by this+0x10.
struct TimerData {
    void (*callback)(int);  // +0x00: function pointer called with argument 1 on timeout
    short active;           // +0x04: non-zero while timer is running
    short timeRemaining;    // +0x06: countdown value (frames?).
};

void TimerEvent::update() {
    TimerData* pTimerData = *(TimerData**)(this + 0x10);   // this+0x10 -> pointer to timer data

    // Only proceed if timer is active
    if (pTimerData->active) {
        pTimerData->timeRemaining--;

        // If counter reached zero, fire the callback
        if (pTimerData->timeRemaining == 0) {
            pTimerData->callback(1);
        }
    }

    // Post-update hook (possibly debug output or signal)
    FUN_009f01a0();
}