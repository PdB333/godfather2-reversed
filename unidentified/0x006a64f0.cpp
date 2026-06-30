// FUN_NAME: SomeManager::removeEntryById
void __thiscall SomeManager::removeEntryById(int thisPtr, int idToRemove)
{
    // Offset +0x678: m_entryCount (number of active entries)
    int count = *(int *)(thisPtr + 0x678);
    if (count < 0) return;

    // Array starts at +0x538, each entry is 0x28 bytes.
    // Search backward from the last entry for the matching id.
    int *entry = (int *)(thisPtr + 0x538 + count * 0x28); // Points past last entry initially.
    int idx = count;
    while (1) {
        idx--;
        entry -= 10; // Each int is 4 bytes, so 10 ints = 0x28 bytes, moving to previous entry.
        if (idx < 0) return;
        if (*entry == idToRemove) break;
    }

    // Found at index 'idx'.
    // Shift all entries from (idx+1) to (count) one slot to the left.
    int shiftIdx = idx + 1;
    if (shiftIdx <= count) {
        // destSlot = &m_entryArray[shiftIdx - 1] (offset +0x510 + shiftIdx*0x28)
        // srcSlot  = &m_entryArray[shiftIdx]
        int *shiftPtr = (int *)(thisPtr + 0x510 + shiftIdx * 0x28);
        do {
            FUN_006a5620(shiftPtr + 10); // This function likely moves or clears the entry at srcSlot.
            shiftIdx++;
            shiftPtr += 10;
        } while (shiftIdx <= count);
    }

    // Clear the last slot (which is now unused after decrementing count).
    int *lastSlot = (int *)(thisPtr + 0x538 + count * 0x28);
    lastSlot[0] = 0; // Clear id field at +0x0
    int *dataPtr = (int *)(thisPtr + 0x53c + count * 0x28); // Pointer field at +0x4
    if (*dataPtr != 0) {
        FUN_004daf90(dataPtr); // Release this pointer
        *dataPtr = 0;
    }
    *(int *)(thisPtr + 0x558 + count * 0x28) = 0; // Clear field at +0x20
    *(int *)(thisPtr + 0x55c + count * 0x28) = 0; // Clear field at +0x24

    // Decrement the count.
    *(int *)(thisPtr + 0x678) = count - 1;
}