// FUNC_NAME: SlotManager::removeSlotEntry
void SlotManager::removeSlotEntry(int slotIndex)
{
    // Check primary slot (offset 0x564) and secondary slot (offset 0x565) in the global manager structure
    char primaryState = *(char *)(gManagerInstance + 0x564);
    char secondaryState = *(char *)(gManagerInstance + 0x565);

    // Process primary slot if not in sentinel state (0x12)
    if (primaryState != 0x12) {
        int primaryId = gSlotPrimaryIDs[slotIndex * 2];  // retrieve ID for this slot
        processStateChange(primaryState);                // handle state transition
        int currentId = getCurrentId();                  // get current ID from some context

        if (currentId == primaryId) {
            removePrimarySlot(slotIndex);                // direct removal if IDs match
        } else {
            // Search the primary ID list for the ID and compact it if found
            int listSize = gPrimaryListSize;
            for (int i = listSize - 1; i >= 0; i--) {
                if (gPrimaryList[i] == primaryId) {
                    // Remove by shifting left
                    for (int j = i; j < listSize - 1; j++) {
                        gPrimaryList[j] = gPrimaryList[j + 1];
                    }
                    gPrimaryListSize--;
                    break;
                }
            }
        }
    }

    // Process secondary slot similarly
    if (secondaryState != 0x12) {
        int secondaryId = gSlotSecondaryIDs[slotIndex * 2];  // retrieve ID for this slot
        processStateChange(secondaryState);
        int currentId = getCurrentId();

        if (currentId == secondaryId) {
            removeSecondarySlot(slotIndex);
            return;  // early return after secondary removal
        } else {
            // Search the secondary ID list and compact
            int listSize = gSecondaryListSize;
            for (int i = listSize - 1; i >= 0; i--) {
                if (gSecondaryList[i] == secondaryId) {
                    // Remove by shifting left
                    for (int j = i; j < listSize - 1; j++) {
                        gSecondaryList[j] = gSecondaryList[j + 1];
                    }
                    gSecondaryListSize--;
                    break;
                }
            }
        }
    }
}