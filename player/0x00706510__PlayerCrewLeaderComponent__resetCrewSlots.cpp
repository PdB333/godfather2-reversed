// FUNC_NAME: PlayerCrewLeaderComponent::resetCrewSlots
void __thiscall PlayerCrewLeaderComponent::resetCrewSlots(int thisPtr, int forceReset)
{
    // +0xf0: pointer to external game manager / player state object
    int *externalObj = *(int **)(thisPtr + 0xf0);
    if (externalObj != 0) {
        // Release any pending resources or sounds associated with the crew
        externalRelease(forceReset);  // FUN_007a03a0

        // Call a virtual method at vtable offset 600 (method index 150) on the external object
        // Typically this is an engine-level update or cleanup call
        (*(void (__thiscall **)(int, int))(*(int *)externalObj + 600))(externalObj, 0);

        if (forceReset != 0) {
            forceUpdateCrewUI();  // FUN_00706490
        }

        globalCleanup();  // FUN_00704a70

        // Array of 11 crew slots, each slot is 20 bytes (5 ints), starting at +0x18
        int *slotArray = (int *)(thisPtr + 0x18);
        for (int i = 0; i < 11; i++) {
            int *slot = slotArray + i * 5;  // Each slot is 5 ints
            // slot[2] = if slot[3] != 0 then 0 else 0 (always zero)
            slot[2] = (~-(uint)(slot[3] != 0)) & slot[3];  // Equivalent to slot[2] = 0

            // slot[0] is the slot ID (0 = empty, 0x48 = locked/reserved)
            if (slot[0] != 0 && slot[0] != 0x48) {
                freeCrewSlotData(slot);  // FUN_004daf90
                slot[0] = 0;  // Mark slot as empty
            }
        }

        // Clear specific flags on the external object (likely dirty flags)
        uint *flags1 = (uint *)(externalObj + 0x249c);
        *flags1 &= 0xfffdffff;  // Clear bit 17 (0x20000)
        uint *flags2 = (uint *)(externalObj + 0x24a0);
        *flags2 &= 0xfff7ffff;  // Clear bit 18 (0x40000)
    }
}