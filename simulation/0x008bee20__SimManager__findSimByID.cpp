// FUNC_NAME: SimManager::findSimByID
int __thiscall SimManager::findSimByID(int thisPtr, int simID) {
    unsigned int count = *(unsigned int*)(thisPtr + 0x134); // number of entries in pool
    int entryBase = *(int*)(thisPtr + 0x130);              // pointer to first entry (0x1c each)
    unsigned int index = 0;
    int entryPtr = 0;

    if (count != 0) {
        entryPtr = entryBase;
        while (*(int*)(entryPtr + 8) != simID) { // compare ID at offset +0x08
            index++;
            entryPtr += 0x1c;                     // move to next entry (28 bytes)
            if (index >= count) {
                return 0;                         // not found
            }
        }
    }
    return entryPtr;                              // pointer to matching entry
}