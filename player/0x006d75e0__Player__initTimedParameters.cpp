// FUNC_NAME: Player::initTimedParameters
void __thiscall Player::initTimedParameters(void* this, int someArg) {
    // Call to some initialization helper (likely sets up a timer or state)
    FUN_006bfa70(someArg);

    float currentVal = *(float*)((int)this + 0x240); // +0x240: current duration or progress value
    float maxVal = g_maxValue;                        // DAT_00d5780c: maximum threshold

    *(uint8*)((int)this + 0x248) = 1;                 // +0x248: flag indicating timed state active

    if (maxVal <= currentVal) {
        // At or above max, use base value directly
        *(int*)((int)this + 0x23C) = g_baseValue;     // +0x23C: computed integer (e.g., remaining time or score)
    } else {
        // Scale down from base value based on current progress
        int scaled = (int)(currentVal * g_scaleFactor + 0.5f); // ROUND
        *(int*)((int)this + 0x23C) = g_baseValue - scaled;
    }

    // Zero out two fields at +0x258 and +0x25C (likely counters or cooldown timers)
    *(int*)((int)this + 0x258) = 0;  // +0x258
    *(int*)((int)this + 0x25C) = 0;  // +0x25C
}