// FUNC_NAME: SomeManager::cleanupSlots
// Function address: 0x00672fd0
// Cleans up an array of 7 slots, each holding a pointer to an allocated block.
// The block has an index at offset -8 and actual data pointer at the given address.
// The class manages a resource table with a counter at +0x04 and an array at +0x0c.

void SomeManager::cleanupSlots() {
    // Pointer to the start of the slot array (structs of size 0x40)
    SlotEntry* slotArray = reinterpret_cast<SlotEntry*>(reinterpret_cast<char*>(this) + 0x34);

    for (int i = 0; i < 7; i++) {
        SlotEntry& slot = slotArray[i]; // each slot is 0x40 bytes

        if (slot.dataPtr != nullptr) {
            // The dataPtr points into an allocated block; the block starts 0x10 bytes before.
            // At offset -8 there is an integer index used to zero out a pointer in the array at +0x0c.
            int index = *reinterpret_cast<int*>(reinterpret_cast<char*>(slot.dataPtr) - 8);
            // Clear the pointer in the table at +0x0c (array of pointers)
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x0c + index * 4) = 0;
            // Decrease the counter at +0x04
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x04) -= 1;
            // Free the actual allocation (starting 0x10 before the data pointer)
            // DAT_01206694 is a deallocation function pointer
            reinterpret_cast<void (*)(void*)>(DAT_01206694)(reinterpret_cast<char*>(slot.dataPtr) - 0x10);
        }

        // Reset slot fields
        slot.dataPtr = nullptr;          // +0x00
        slot.field_0x1c = 0;             // +0x1c (offset 28)
        slot.field_0x38 = 1;             // +0x38 (offset 56)
    }
}