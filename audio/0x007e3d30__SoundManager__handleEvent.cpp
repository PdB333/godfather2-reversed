// FUNC_NAME: SoundManager::handleEvent
void __thiscall SoundManager::handleEvent(uint eventId)
{
    int *pEntry;
    int *pCurrentEntry;
    int entryId;
    int currentId;
    bool found;

    pEntry = nullptr;
    found = findEntry(this + 0x98, eventId, &pEntry); // lookup in first sound list
    if (found) {
        if (*pEntry != 0) {
            if (*pEntry != 0x48) { // 0x48 = invalid/null ID
                stopSound(*(uint *)(this + 0x58)); // stop current sound
            }
            if ((*pEntry != 0) && (entryId = *pEntry, entryId != 0x48)) {
                pCurrentEntry = (int *)(this + 0x84);
                if (*(int *)(this + 0x84) == 0) {
                    currentId = 0;
                } else {
                    currentId = *(int *)(this + 0x84) - 0x48;
                }
                if (entryId - 0x48 == currentId) {
                    if (*pCurrentEntry != 0) {
                        releaseEntry(pCurrentEntry); // free current entry
                        *pCurrentEntry = 0;
                    }
                    resetCurrentEntry(); // global reset
                }
            }
        }
        cleanupEntry(&eventId, &pEntry); // free temporary lookup result
        found = findEntry(this + 0xac, eventId, &pEntry); // lookup in second sound list
        if (found) {
            if ((*pEntry != 0) && (*pEntry != 0x48)) {
                playSound(*(uint *)(this + 0x58)); // play new sound
            }
            cleanupEntry(&eventId, &pEntry);
        }
    }
    return;
}