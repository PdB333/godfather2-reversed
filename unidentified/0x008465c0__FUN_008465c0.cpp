// FUNC_NAME: SomeClass::updateCooldownCounter
uint __fastcall SomeClass::updateCooldownCounter(int thisPtr)
{
    uint timeResult = FUN_004035a0(); // likely a time or condition check
    if ((char)timeResult == '\0') {
        *(short *)(thisPtr + 0x154) = 0; // +0x154: cooldown counter (short)
        return timeResult & 0xffffff00;   // return high 24 bits (timeResult without low byte)
    }
    // Increment counter
    *(short *)(thisPtr + 0x154) = *(short *)(thisPtr + 0x154) + 1;
    // Check if counter exceeded threshold (4)
    if (4 < *(short *)(thisPtr + 0x154)) {
        *(short *)(thisPtr + 0x154) = 0; // reset counter
        return 1; // indicate cooldown expired
    }
    return 0; // cooldown still active
}