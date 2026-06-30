// FUNC_NAME: PlayerSM::updateStateMachine
void __thiscall PlayerSM::updateStateMachine(int thisPtr, int *stateIdPtr)
{
    // Check if current state matches a specific game state (DAT_0120e93c)
    if (*stateIdPtr == DAT_0120e93c) 
    {
        // Call base class method with argument 6 (likely setBaseState or startTimer)
        BaseStateMachine::setState(thisPtr - 0x3c, 6);

        // Check bit 11 (0x800) of flags at offset +0x194
        if (((*(uint *)(thisPtr + 0x194) >> 0xb) & 1) != 0)
        {
            // If flag set and some counter (offset +0x1a4) is zero, call function
            if (*(int *)(thisPtr + 0x1a4) == 0)
            {
                sub_00709280();
            }
        }

        // Condition: currentState (offset +0x1d8) is either 0 or 0x48 AND nextState (offset +0x254) is 0
        if ((*(int *)(thisPtr + 0x1d8) == 0) || (*(int *)(thisPtr + 0x1d8) == 0x48))
        {
            if (*(int *)(thisPtr + 0x254) == 0)
            {
                // Perform transition: pass pointers to state data and next state
                sub_00708f80(thisPtr + 0x244, thisPtr + 0x254);
                // Clear bit 12 (0x1000) of flags
                *(uint *)(thisPtr + 0x194) &= 0xFFFFEFFF;
            }
        }

        // If subState (byte at +0x170) is less than 25 (0x19)
        if (*(byte *)(thisPtr + 0x170) < 0x19)
        {
            // Call base class update function
            BaseStateMachine::update(thisPtr - 0x3c);
        }

        // If timer (float at +0x26c) is non-zero and bit 3 of flags is clear (not in specific state)
        if ((*(float *)(thisPtr + 0x26c) != 0.0f) && ((*(uint *)(thisPtr + 0x194) >> 3) & 1) == 0)
        {
            *(float *)(thisPtr + 0x26c) = 0.0f; // Reset timer
        }

        // Call global function with DAT_0120e93c (maybe update state timer)
        sub_004086d0(&DAT_0120e93c);
    }

    // Cleanup/destructor call on the state ID pointer
    sub_0046efc0(stateIdPtr);
}