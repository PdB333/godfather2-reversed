// FUNC_NAME: PlayerStateMachine::update
void __fastcall PlayerStateMachine::update(int *this)
{
    // Offset 0x94: some counter or pointer related to animation state
    int someCounter = this[0x25];
    float someFloat = FUN_0076ec60(); // Likely returns delta time or a random value

    // Global pointer at DAT_012233a0+4, dereferenced once then subtract 0x1f30
    int* globalPtr = *(int**)(DAT_012233a0 + 4);
    int globalAdjusted = (globalPtr != 0) ? (*globalPtr - 0x1f30) : 0;

    int currentState = this[0x22]; // Offset 0x88: current state ID

    if (currentState == 3)
    {
        // State 3: check if someId (offset 0x5c) is valid and not 0x48
        int someId = this[0x17]; // Offset 0x5c
        if (someId != 0 && someId != 0x48)
        {
            // Compute index: if someId == 0 then 0 else someId - 0x48
            int index = (someId == 0) ? 0 : (someId - 0x48);
            FUN_0046fd90(index, 0); // Likely stop/cleanup an animation or sound
        }

        // Set a flag at offset 0x54 (byte) bit 3 (0x8) if not already set
        if ((*(byte*)(this + 0x15) & 8) == 0) // byte offset = 0x54 (this + 0x15*4? Decompiler may have misaligned)
        {
            FUN_007f4490(1, 0, DAT_00d5ef90); // Possibly enable HUD or input
            *(byte*)(this + 0x15) |= 8;
        }

        // Call virtual function at vtable+0x2c (index 11) with specific hash and parameters
        // Likely plays a sound/animation with ID 0x81cfd529, volume 1.0, pitch 1.0
        (**(code**)(*this + 0x2c))(0x81cfd529, 1, 1, 0, 0x3f800000, 0x3f800000);
        return;
    }

    // Check if state is 4 or has flag 0x8 from FUN_0084d420
    unsigned int stateFlags = FUN_0084d420(currentState);
    if (currentState == 4 || (stateFlags & 8) != 0)
    {
        // Clear something at offset 0x78 (likely a timer or reference)
        FUN_0046ffe0(this + 0x1e, 0);

        // Set a flag in the large object pointed to by this[0x14] (offset 0x50)
        // That object has a field at +0x1b94 (offset in that object)
        *(unsigned int*)(this[0x14] + 0x1b94) |= 8;

        // Set the same flag bit in this
        if ((*(byte*)(this + 0x15) & 8) == 0)
        {
            FUN_007f4490(1, 0, DAT_00d5ef90);
            *(byte*)(this + 0x15) |= 8;
        }

        // Play animation/sound with different hash 0xc996f012
        (**(code**)(*this + 0x2c))(0xc996f012, 1, 1, 0, 0x3f800000, 0x3f800000);
        return;
    }

    // For all other states: check flags via FUN_0084d420 again
    unsigned int flags2 = FUN_0084d420(this[0x22]); // Re-fetch? Redundant but maybe different call
    if ((flags2 & 0x40) != 0)
    {
        return;
    }

    char charFlag = FUN_0084d420(this[0x22]); // Actually returns char? decompiler may be truncated
    if (charFlag < 0) // Check sign bit (likely bit 7)
    {
        return;
    }

    // Check second ID at offset 0x64
    int secondId = this[0x19];
    if (secondId != 0 && secondId != 0x48)
    {
        int index2 = (secondId == 0) ? 0 : (secondId - 0x48);
        int computedCheck = index2;
        // If computedCheck equals globalAdjusted, and state has flag 0x1, and some conditions
        if ((computedCheck == globalAdjusted) &&
            ((FUN_0084d420(this[0x22]) & 1) != 0) &&
            (FUN_007fd640() == 0) && // Possibly a progress check
            (*(char*)(this[0x14] + 0x1ec5) != -1) &&
            (FUN_00690150(0x66) != 0)) // Some availability check (e.g., animation slot free)
        {
            int vtableIndex = *(int*)(this[0x14] + 0x1ecc); // Another index from large object
            char animeSlot = *(char*)(this[0x14] + 0x1ec5);
            if ((animeSlot != -1) && (animeSlot < 0x3c) && (vtableIndex < 5))
            {
                // Use a lookup table at DAT_00d66380 to determine which sound/animation ID to play
                // Formula: DAT_00d66380 + (animeSlot * 0x19 + vtableIndex) * 4
                unsigned int soundHash = *(unsigned int*)(&DAT_00d66380 + (animeSlot * 0x19 + vtableIndex) * 4);
                (**(code**)(*this + 0x2c))(soundHash, 1, 1, 0, 0x3f800000, 0x3f800000);
                return;
            }
        }
    }

    // Fallback: call generic animation/sound update
    FUN_0076e860(someCounter, someFloat);
}