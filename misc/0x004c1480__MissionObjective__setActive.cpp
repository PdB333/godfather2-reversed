// FUNC_NAME: MissionObjective::setActive
void __fastcall MissionObjective::setActive(int thisPtr)
{
    // +0x1C4: flags field (bit 6 = 0x40 means active flag)
    uint32_t flags = *(uint32_t *)(thisPtr + 0x1C4);
    if ((flags & 0x40) == 0)
    {
        // Set the active flag
        *(uint32_t *)(thisPtr + 0x1C4) = flags | 0x40;
        // Global gGameState is non-null when game state is available
        if (gGameState != 0)
        {
            // Copy objective data from (thisPtr + 0x3C) into gGameState
            FUN_00407e60(thisPtr + 0x3C, &gGameState);
        }
    }
    // +0x1C0: pointer to an active operation or reference count
    if (*(int *)(thisPtr + 0x1C0) != 0)
    {
        // Possibly two decrement/release calls
        FUN_004c23f0(0);
        FUN_004c23f0(0);
    }
    return;
}