// FUNC_NAME: GameItem::getDataPointer
int __fastcall GameItem::getDataPointer(GameItem* thisPtr)
{
    // +0x08 -> pointer to a manager/table manager
    GameItemManager* manager = *(GameItemManager**)((uintptr_t)thisPtr + 0x08);
    // +0x0C -> item type ID to search for
    int itemTypeID = *(int*)((uintptr_t)thisPtr + 0x0C);

    uint entryIndex = 0;
    uint numEntries = *(uint*)((uintptr_t)manager + 0x08);
    ItemTypeEntry* entryArray = *(ItemTypeEntry**)((uintptr_t)manager + 0x04);
    ItemTypeEntry* foundEntry = nullptr;

    if (numEntries != 0) {
        do {
            if (entryArray[entryIndex].typeID == itemTypeID) {
                foundEntry = &entryArray[entryIndex];
                goto found;
            }
            entryIndex++;
        } while (entryIndex < numEntries);
    }
    // Not found: fallback to null entry
    foundEntry = nullptr;

found:
    // +0x04 -> index into a data table (e.g., weapon index)
    int dataIndex = *(int*)((uintptr_t)thisPtr + 0x04);
    // +0x24 in foundEntry -> pointer to a table of integer offsets (size = int*)
    int* offsetTable = *(int**)((uintptr_t)foundEntry + 0x24);
    // +0x10 in manager -> base address for the data array
    int dataBase = *(int*)((uintptr_t)manager + 0x10);

    // Compute: offset = offsetTable[dataIndex] * 32 + dataBase
    int offset = offsetTable[dataIndex] * 32 + dataBase;
    return offset;
}