//FUNC_NAME: EntityManager::findEntryByKey
uint __thiscall EntityManager::findEntryByKey(int this, int keyObject) {
    // Table of 4 entries at this+0x10, each entry is 24 bytes (6 ints)
    // Entry layout:
    //   +0x00: field0 (int)
    //   +0x04: field1 (int)
    //   +0x08: field2 (int)
    //   +0x0C: field3 (int)
    //   +0x10: ptr (void*)  // pointer to a parent structure
    //   +0x14: padding/unused
    int* entryPtr = (int*)(this + 0x10);
    uint index = 0;
    do {
        bool match = false;
        // keyObject+0x1F54 is a bitfield; bit 1 selects comparison mode
        if ((*(uint*)(keyObject + 0x1F54) >> 1) & 1) {
            // Pointer mode: compare entry's ptr with keyObject
            // entry->ptr points to a parent structure that contains keyObject at offset 0x48
            if (*entryPtr == 0) {
                match = (keyObject == 0);
            } else {
                match = (*entryPtr - 0x48 == keyObject);
            }
        } else {
            // Four-int mode: compare entry's first four ints with keyObject's fields at +0x20..+0x2C
            if (entryPtr[-4] == *(int*)(keyObject + 0x20) &&
                entryPtr[-3] == *(int*)(keyObject + 0x24) &&
                entryPtr[-2] == *(int*)(keyObject + 0x28) &&
                entryPtr[-1] == *(int*)(keyObject + 0x2C)) {
                match = true;
            }
        }
        if (match) {
            // Return pointer to entry (low byte cleared) with success flag (low byte = 1)
            return ((uint)entryPtr & 0xFFFFFF00) | 1;
        }
        index++;
        entryPtr += 6; // advance to next entry (6 ints = 24 bytes)
        if (index > 3) {
            // No match found; return pointer past last entry with low byte zeroed
            return (uint)entryPtr & 0xFFFFFF00;
        }
    } while (true);
}