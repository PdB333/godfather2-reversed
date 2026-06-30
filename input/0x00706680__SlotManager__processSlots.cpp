// FUNC_NAME: SlotManager::processSlots
// Function address: 0x00706680
// Scans an array of 11 slot entries (each 20 bytes) starting at +0x18.
// If the first field of an entry is 0 or 0x48 (72), calls clearSlot with the index.
// Only runs if the flag at +0xf0 is non-zero.

void __fastcall SlotManager::processSlots(int thisPtr) {
    if (*(int*)(thisPtr + 0xf0) != 0) {
        for (unsigned int slotIndex = 0; slotIndex < 11; slotIndex++) {
            // Each slot entry is 5 ints (20 bytes)
            int* slotFirstField = (int*)(thisPtr + 0x18 + slotIndex * 20);
            if (*slotFirstField == 0 || *slotFirstField == 0x48) {
                // Slot is empty or in a special state; clear it
                clearSlot(slotIndex); // FUN_00706380
            }
        }
    }
}