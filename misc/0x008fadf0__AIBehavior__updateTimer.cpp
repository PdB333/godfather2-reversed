// FUNC_NAME: AIBehavior::updateTimer
// Address: 0x008fadf0
// Role: Updates a timer and triggers an event when conditions are met.
// Fields: this+0x164 (float) - timerDuration, this+0x168 (float) - timerRemaining,
//         this+0x170 (uint) - flags, this+0x42c (float) - triggerThreshold

int __thiscall AIBehavior::updateTimer(void* this, undefined4 param2, float deltaTime)
{
    uint flags;
    float10 randomFactor;
    float newRemaining;
    int quotient;

    // If the timer duration is positive, decrement the remaining time
    if (*(float*)((int)this + 0x164) > 0.0f)
    {
        newRemaining = *(float*)((int)this + 0x168) - deltaTime;
        *(float*)((int)this + 0x168) = newRemaining;
        if (newRemaining <= 0.0f)
        {
            *(int*)((int)this + 0x168) = 0;
        }

        flags = *(uint*)((int)this + 0x170);
        // Check if bit10 is clear AND (duration <= threshold OR bit7 set)
        if (((flags >> 10 & 1) == 0) &&
            (*(float*)((int)this + 0x42c) <= *(float*)((int)this + 0x164) || ((flags >> 7 & 1) != 0)))
        {
            // Trigger some effect (sound/event) using global data
            int localData[3];
            localData[0] = DAT_0112fe80;  // +0x00
            localData[1] = 0;             // +0x04
            localData[2] = 0;             // +0x08
            FUN_00408a00(localData, 0);   // playSoundEffect or triggerEvent
            *(uint*)((int)this + 0x170) = flags | 0x400;  // set bit10 (triggered)
        }

        randomFactor = FUN_008fa720();  // getRandomFactor (maybe 0..1)
        if ((flags & 0x80) == 0)       // if bit7 clear, reduce duration by random*deltaTime
        {
            *(float*)((int)this + 0x164) -= (float)randomFactor * deltaTime;
        }

        if (*(float*)((int)this + 0x164) <= 0.0f)
        {
            FUN_008fac30(1, 0);          // onTimerExpired
            *(int*)((int)this + 0x164) = 0;
        }

        // Update a periodic flag based on global frame count
        quotient = DAT_01205220 * -0x33333333;  // DAT_01205220 / 5
        if (DAT_01205220 == (DAT_01205220 / 5) * 5)
        {
            *(uint*)((int)this + 0x170) |= 0x40;    // set bit6
        }
        else
        {
            *(uint*)((int)this + 0x170) &= ~0x40;   // clear bit6
        }
    }
    return quotient;   // not used meaningfully? maybe side effect
}