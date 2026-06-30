// FUNC_NAME: Entity::checkTimerElapsed
// Function at 0x0054f460: Checks if a timer at offset +0xB0 has elapsed relative to the current time.
// Returns a 32-bit value where low byte = 1 if elapsed, else 0; upper 24 bits preserve the timer's high bits.
uint __thiscall Entity::checkTimerElapsed(float deltaMax)
{
    uint timer = *(uint *)((byte *)this + 0xB0); // +0xB0: stored timestamp/state
    if (timer != 0)
    {
        int timeDiff = (int)(g_currentTime - timer); // g_currentTime = DAT_01205224
        float fTimeDiff = (float)timeDiff;
        if (timeDiff < 0)
        {
            fTimeDiff += g_timeWrapConstant; // DAT_00e44578: wrap-around adjustment (likely 2^32 as float)
        }
        float scaledDiff = fTimeDiff * g_timeScale; // DAT_00e2e210: time speed factor
        if (deltaMax <= scaledDiff)
        {
            // Timer elapsed: set low byte to 1, keep high 24 bits unchanged
            return (timer & 0xFFFFFF00) | 1;
        }
    }
    // Not elapsed or timer zero: clear low byte
    return timer & 0xFFFFFF00;
}