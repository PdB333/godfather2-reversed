// FUNC_NAME: EntityManager::hasEntryWithID
bool __thiscall EntityManager::hasEntryWithID(int entryID) {
    // Return false if input ID is zero (invalid/empty ID)
    if (entryID == 0) return false;

    // Get the number of entries stored at this+0xB4 (short)
    short entryCount = *(short*)(this + 0xB4);
    // Array of entries starts at this+0xC4, each entry is 8 bytes (two ints)
    for (short i = 0; i < entryCount; ++i) {
        int* currentEntry = (int*)(this + 0xC4 + i * 8);
        int pointerOrHandle = *currentEntry;

        // Compute the actual entity ID from the stored pointer/handle:
        // If null, ID=0; otherwise subtract 0x48 (expected offset to a base structure)
        int storedID = (pointerOrHandle == 0) ? 0 : (pointerOrHandle - 0x48);

        if (storedID == entryID) {
            return true;
        }
    }
    return false;
}