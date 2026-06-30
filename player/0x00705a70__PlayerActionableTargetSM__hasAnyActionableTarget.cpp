// FUNC_NAME: PlayerActionableTargetSM::hasAnyActionableTarget
// Address: 0x00705a70
// Role: Checks if there are any valid actionable targets in the player's action list.
//        Iterates over an array of action data slots, calling a helper to test each slot's validity.
//        Returns true (1) if at least one slot is valid, false (0) otherwise.

char __thiscall PlayerActionableTargetSM::hasAnyActionableTarget(void* thisPtr)
{
    // thisPtr +0x10 points to a descriptor structure for the action slot array.
    // That descriptor has at offset +4 the number of slots.
    int* actionSlotDescriptor = *(int**)((char*)thisPtr + 0x10); // +0x10: pointer to slot descriptor
    int slotCount = actionSlotDescriptor[1]; // +4: slot count

    char found = 0;
    for (int i = 0; i < slotCount; i++)
    {
        // Helper function at 0x00704110: returns non-zero if slot i is a valid actionable target.
        int isValid = isActionableSlotValid(i); // renamed from FUN_00704110
        if (isValid)
        {
            if (found)
            {
                // Early exit: already have at least one valid slot, return true.
                return 1;
            }
            found = 1;
        }
    }
    return found;
}