// FUNC_NAME: SlotManager::clearSlots
void __fastcall SlotManager::clearSlots(int this)
{
    // Each slot is 24 bytes (6 ints). The array starts at offset 0x10.
    // Slot layout:
    //   +0x00: int (data0)
    //   +0x04: int (data1)
    //   +0x08: int (data2)
    //   +0x0C: int (data3)
    //   +0x10: int* (pointer to dynamically allocated data)
    //   +0x14: int (unused in this function)
    int* slotPtr = (int*)(this + 0x10);
    int count = 4;
    do {
        // Clear the first 4 ints of the slot (offsets 0x00, 0x04, 0x08, 0x0C)
        slotPtr[-1] = 0; // offset 0x0C
        slotPtr[-2] = 0; // offset 0x08
        slotPtr[-3] = 0; // offset 0x04
        slotPtr[-4] = 0; // offset 0x00
        // Free the pointer at offset 0x10 if non-null
        if (*slotPtr != 0) {
            freeSlotPointer(slotPtr); // FUN_004daf90 - deallocates the pointed data
            *slotPtr = 0;
        }
        slotPtr += 6; // advance to next slot (24 bytes)
        count--;
    } while (count != 0);
}