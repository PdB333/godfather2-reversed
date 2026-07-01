// FUNC_NAME: Player::handleTimer
int __fastcall Player::handleTimer(int this) {
    int result = 0;
    int* timerCountdown = (int*)(this + 0x294c); // countdown timer (decrement per tick)
    uint* flags = (uint*)(this + 0x249c); // state flags (bit 1 = timer expired trigger)

    if (*timerCountdown > 0) {
        // Decrement the timer
        int newVal = *timerCountdown - 1;
        *timerCountdown = newVal;
        if (newVal == 0) {
            // Timer reached zero: set flag bit 1 (trigger event)
            *flags |= 2;
            // Notify timer expiry system (param 0 indicates no additional data)
            FUN_009ae900(0);
            result = 1; // Indicate that timer expired this tick
        }
    }
    return result; // Returns 1 if timer expired, 0 otherwise
}