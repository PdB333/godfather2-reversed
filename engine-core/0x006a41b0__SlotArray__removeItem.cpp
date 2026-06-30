// FUNC_NAME: SlotArray::removeItem
// Function at 0x006a41b0: Removes an item from a slot array by ID if a condition flag is zero. 
// The array is stored as a pointer at +0x58, with count at +0x54. Each slot is 0x30 bytes, with ID at offset 0x10.
void __thiscall SlotArray::removeItem(int thisPtr, int id, int conditionFlag, uint callbackParam)
{
    int count;
    int *slotPtr;
    int index;

    if (conditionFlag == 0) {
        count = *(int *)(thisPtr + 0x54);
        if (0 < count) {
            // Iterate through slots to find the one with the matching ID.
            // slotPtr starts at the ID field of the first slot (base + 0x10). Each slot is 0x30 bytes.
            slotPtr = (int *)(*(int *)(thisPtr + 0x58) + 0x10);
            index = 0;
            while (*slotPtr != id) {
                index++;
                slotPtr = slotPtr + 0xC; // Increment by 0x30 bytes (0xC ints) to next slot's ID field.
                if (count <= index) {
                    return;
                }
            }
            // Found the slot; call a callback with (id, 0, callbackParam) and clear the first DWORD at slot offset 0x10.
            FUN_006a5690(id, 0, callbackParam);
            *(uint *)(index * 0x30 + 0x10 + *(int *)(thisPtr + 0x58)) = 0;
        }
    }
    return;
}