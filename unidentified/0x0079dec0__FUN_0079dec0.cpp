// FUNC_NAME: SomeManager::updateStealthTimer
// Address: 0x0079dec0
// Called each frame to check stealth timer condition and clear bit if expired.

void __fastcall SomeManager::updateStealthTimer(int thisPtr)
{
    // Call base update or service routine
    FUN_007ff7e0();

    // Check if stealth mode flag (bit 9 at +0x24a4) is set
    // and if currentTime + stealthStartTime [at +0x3110] is still less than maxStealthDuration
    // If condition met, clear the flag (disable stealth)
    if (((*(unsigned int*)(thisPtr + 0x24A4) >> 9) & 1) != 0 &&
        (*(float*)(thisPtr + 0x3110) + g_currentTime < g_stealthMaxDuration))
    {
        // Clear bit 9 (mask 0x200) in stealth flags
        *(unsigned int*)(thisPtr + 0x24A4) &= 0xFFFFFDFF; // ~0x200
    }
}