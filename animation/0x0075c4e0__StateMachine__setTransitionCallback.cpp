// FUNC_NAME: StateMachine::setTransitionCallback
// Address: 0x0075c4e0
// Role: Configures a delegate/callback for state transitions based on enable flag.
// Sets a flag at +0x80 and three member-function pointer slots at +0xf4, +0xfc, +0x104.

void __thiscall StateMachine::setTransitionCallback(int thisPtr, bool enable)
{
    // +0x80: flag bit 0 indicates whether callback is active
    if (!enable)
    {
        *(unsigned int *)(thisPtr + 0x80) &= ~1;
        // Use no-transition callback function (address 0x0075b580)
        *(unsigned long long *)(thisPtr + 0xf4) = ( (unsigned long long)(0x0075b580) << 32 ) | (unsigned int)thisPtr;
    }
    else
    {
        *(unsigned int *)(thisPtr + 0x80) |= 1;
        // Use transition callback function (address 0x0075b570)
        *(unsigned long long *)(thisPtr + 0xf4) = ( (unsigned long long)(0x0075b570) << 32 ) | (unsigned int)thisPtr;
    }

    // Writes at +0xfc and +0x104 appear to set additional delegate slots,
    // but the source values (uStack_c, local_8) are uninitialized in the decompilation.
    // Possibly these are additional parameters or the decompilation is incomplete.
    // They are preserved here as written, though they may be erroneous.
    unsigned int stackGarbage;
    unsigned int localGarbage;
    // +0xfc: another delegate slot (high part only, low set to zero)
    *(unsigned long long *)(thisPtr + 0xfc) = (unsigned long long)stackGarbage << 32;
    // +0x104: delegate slot with fixed function address 0x0075b6b0 and garbage 'this' pointer
    *(unsigned long long *)(thisPtr + 0x104) = ( (unsigned long long)(0x0075b6b0) << 32 ) | localGarbage;
}