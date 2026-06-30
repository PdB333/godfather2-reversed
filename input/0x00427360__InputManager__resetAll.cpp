// FUNC_NAME: InputManager::resetAll

void InputManager::resetAll(void)
{
    // First part: destroy all objects pointed to by a global pointer table.
    // The table is a large array of pointers (starting at DAT_012083f4) ending at 0x120a3f4.
    // Each non-null pointer is assumed to have a vtable; the third method (offset 8) is a destructor.
    int** pTableEntry = &DAT_012083f4;
    do {
        int* pObject = *pTableEntry;
        if (pObject != nullptr) {
            // Call the destructor via vtable (offset 0x08 = 3rd virtual method)
            (**(code**)(*pObject + 8))(pObject);
            *pTableEntry = nullptr; // Clear pointer after destruction
        }
        pTableEntry++;
    } while ((int)pTableEntry < 0x120a3f4);

    // Second part: reset all input slots (128 slots, each with a count and array of structures).
    // The base of the slot array is derived from a global singleton (DAT_012053cc) + 0x4c.
    uint* pSlot = (uint*)(DAT_012053cc + 0x4c);
    int slotCount = 0x80; // 128 slots
    do {
        // Clear a field at offset -36 bytes from the current slot pointer (e.g., last active button ID)
        pSlot[-9] = 0xffffffff; // Resetting to -1 (invalid)

        if (*pSlot != 0) { // If this slot has a non-zero count
            uint count = 0;
            int byteOffset = 0;
            do {
                // For each element in the slot's array (each element size 0x50 = 80 bytes),
                // reset a field at offset 0x28 to -1 (e.g., button state, timestamp)
                *(int*)(pSlot[-1] + 0x28 + byteOffset) = 0xffffffff;
                count++;
                byteOffset += 0x50;
            } while (count < *pSlot);
        }

        pSlot += 0x18; // Move to next slot (24 bytes per slot structure)
        slotCount--;
    } while (slotCount != 0);
}