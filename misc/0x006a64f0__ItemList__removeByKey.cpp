// FUNC_NAME: ItemList::removeByKey
// Function address: 0x006a64f0
// Removes an item from the dynamic array by matching its first field (key).
// Array starts at +0x538, each entry 0x28 bytes (10 ints).
// Count at +0x678.
// Fields per entry: +0x00 key (int), +0x04 pointer (allocated), +0x20 value1, +0x24 value2.

void __thiscall ItemList::removeByKey(int key)
{
    int count = *(int *)(this + 0x678);
    if (count < 0) return;

    int *entryPtr = (int *)(this + 0x538 + count * 0x28);
    int idx = count;
    while (*entryPtr != key) {
        idx--;
        entryPtr -= 10; // move to previous entry (10 ints per entry)
        if (idx < 0) return;
    }

    if (idx >= 0) {
        int shiftIdx = idx + 1;
        if (shiftIdx <= count) {
            int *shiftDest = (int *)(this + 0x510 + shiftIdx * 0x28); // points to entry at idx (shiftDest+0x28 is next)
            do {
                shiftElement(shiftDest + 0x28); // copy next entry into current slot
                shiftIdx++;
                shiftDest += 10;
            } while (shiftIdx <= *(int *)(this + 0x678));
        }

        // Clear the last (now duplicate) entry
        int lastIdx = *(int *)(this + 0x678);
        *(int *)(this + 0x538 + lastIdx * 0x28) = 0; // key = 0
        int *ptrField = (int *)(this + 0x53c + lastIdx * 0x28);
        if (*ptrField != 0) {
            freeMemory(ptrField);
            *ptrField = 0;
        }
        *(int *)(this + 0x558 + lastIdx * 0x28) = 0; // value1 = 0
        *(int *)(this + 0x55c + lastIdx * 0x28) = 0; // value2 = 0
        *(int *)(this + 0x678) = count - 1; // decrement count
    }
}