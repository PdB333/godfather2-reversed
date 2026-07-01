// FUNC_NAME: InputManager::updateActiveSlots
void __fastcall updateActiveSlots(int *slotArrayPtr)
{
    // Iterate over 4 slots (stride = 12 bytes per slot, each slot has 3 ints)
    int slotCount = 4;
    do {
        // First field: pointer to an object (non-zero means slot is active)
        if (*slotArrayPtr != 0) {
            // Subtract 0x48 (72) to get the base object (e.g. parent controller/player object)
            int *baseObjectPtr = (int *)(*slotArrayPtr - 0x48);
            if (baseObjectPtr != (int *)0x0) {
                // Get vtable pointer from base object (first word)
                int vtablePtr = *baseObjectPtr;
                // Call virtual function at vtable+0x34 (index 0xD) with global accessor result
                // This likely plays a sound or updates state for the slot owner
                (**(code **)(vtablePtr + 0x34))(FUN_004d94d0());
            }
        }
        // Advance to next slot (3 ints = 12 bytes)
        slotArrayPtr += 3;
        slotCount--;
    } while (slotCount != 0);
}