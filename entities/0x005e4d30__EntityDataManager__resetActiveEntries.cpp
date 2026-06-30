// FUNC_NAME: EntityDataManager::resetActiveEntries
// Address: 0x005e4d30
// Role: Clears data for active entity entries that are still valid, and resets global state flags.

void EntityDataManager::resetActiveEntries()
{
    uint entityId;
    int dataOffset;
    char isValid;
    int globalPtr; // temp for global variable DAT_01223504
    uint *activeEntryPtr;

    int thisBase = this; // base of this object
    activeEntryPtr = (uint *)(this + 0x24); // pointer to array of active entries (12 bytes each, 512 entries)
    int entryCount = 0x200; // 512 entries

    do {
        // Check if active entry is in use (flag at offset +4)
        if (activeEntryPtr[1] != 0) {
            entityId = *activeEntryPtr; // ID at offset +0
            isValid = FUN_005e63e0(entityId); // Check if entity is still valid/alive
            if (isValid != '\0') {
                dataOffset = 0;
                if (entityId < 0x200) {
                    // Compute offset into larger entity data array (0x30 bytes per entry, base at +0x10)
                    dataOffset = entityId * 0x30 + 0x10 + thisBase;
                }
                // Clear four fields in the entity data entry
                *(int *)(dataOffset + 0x20) = 0; // field at +0x20
                *(int *)(dataOffset + 0x18) = 0; // field at +0x18
                *(int *)(dataOffset + 0x2c) = 0; // field at +0x2c
                *(int *)(dataOffset + 0x10) = 0; // field at +0x10 (first field of entry)
            }
        }
        globalPtr = DAT_01223504; // global singleton pointer
        activeEntryPtr = activeEntryPtr + 3; // advance by 12 bytes (3 * uint32)
        entryCount--;
    } while (entryCount != 0);

    // Clear global state flags at +0x1d (byte) and +0x18 (int)
    *(byte *)(DAT_01223504 + 0x1d) = 0;
    *(int *)(DAT_01223504 + 0x18) = 0;
    return;
}