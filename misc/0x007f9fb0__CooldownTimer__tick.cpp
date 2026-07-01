// FUNC_NAME: CooldownTimer::tick
int __thiscall CooldownTimer::tick(void) {
    int counter = *(int *)(this + 0x1f18); // +0x1f18: cooldown counter (ticks remaining)
    if (counter > 0) {
        counter--;
        *(int *)(this + 0x1f18) = counter;
        if (counter == 0) {
            // Cooldown just expired; capture current time
            unsigned int currentTime = getTickCount(); // FUN_0045eea0
            *(unsigned int *)(this + 0x1f14) = currentTime; // +0x1f14: timestamp of expiration
        }
        return 1; // Cooldown still active
    }

    unsigned int storedTime = *(unsigned int *)(this + 0x1f14); // +0x1f14
    if (storedTime != 0) {
        unsigned int currentTime = getTickCount();
        if (storedTime == currentTime) {
            return 1; // Still within the same tick after expiration
        }
        // Time has advanced; reset cooldown state
        *(unsigned int *)(this + 0x1f14) = 0;
        *(int *)(this + 0x1f18) = 0;
    }
    return 0; // Cooldown not active
}