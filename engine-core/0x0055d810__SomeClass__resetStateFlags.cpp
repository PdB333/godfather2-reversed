// FUNC_NAME: SomeClass::resetStateFlags

// Function at 0x0055d810
// Modifies state flags at +0x110 and clears a field at +0xD4.
// __thiscall on 'this' in EAX.
void resetStateFlags(void* thisPtr)
{
    uint* flags = (uint*)((char*)thisPtr + 0x110); // +0x110: bitfield of state flags (bit0..bitN)
    int* timerOrParam = (int*)((char*)thisPtr + 0xD4); // +0xD4: some parameter/timer, always cleared

    // Always set bit 2 (0x4) -- possibly "isActive" or "isProcessing"
    *flags |= 0x4;

    if ((*flags >> 3) & 1) // Check bit 3 (0x8) -- possibly "isPaused" or "isInitialized"
    {
        // If bit 3 set: set bit 4 (0x10), clear bit 3
        *flags |= 0x10;     // Set bit 4 -- maybe "hasCompleted"
        *flags &= ~0x8;     // Clear bit 3
        *timerOrParam = 0;  // Reset timer/parameter to 0
        return;
    }

    // If bit 3 not set: clear both bit 4 and bit 3, reset timer
    *flags &= ~0x10;    // Clear bit 4
    *flags &= ~0x8;     // Clear bit 3
    *timerOrParam = 0;  // Reset timer/parameter to 0
}