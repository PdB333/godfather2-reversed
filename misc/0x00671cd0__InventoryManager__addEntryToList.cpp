// FUNC_NAME: InventoryManager::addEntryToList
// Function address: 0x00671cd0
// Role: Adds a new entry to an item list (probably inventory) with given ID and value, copying default name and stats from the owning object.

// Entry structure: 0xC4 bytes
// +0x00: short itemId
// +0x02: short itemValue
// +0x04: char name[64]   (max 63 chars + null)
// +0x44: short stats[64] (max 64 shorts, terminated by 0)
struct InventoryEntry {
    short itemId;
    short itemValue;
    char name[64];
    short stats[64];
};

// The list container is part of a larger object (the InventoryManager).
// Fields in the larger object (this) used here:
// +0x50: char* defaultName       (source for entry name)
// +0x54: short* defaultStats     (source for entry stats, null terminated)
// +0x180: SomeUIComponent** pUI  (pointer to a UI component with at least two shorts at +0x60 and +0x62)

int InventoryManager::addEntryToList(InventoryEntryList* list, short itemId, short itemValue)
{
    InventoryEntry* newEntry;
    short* srcStats;
    short* dstStats;
    char* dstName;
    uint statIdx;

    // Resize or allocate the list data buffer
    if (list->count == 0) {
        list->data = (InventoryEntry*)FUN_00673070();  // allocate initial buffer
    } else {
        list->data = (InventoryEntry*)FUN_006730f0(list->data, list->count * 0xC4);
    }

    if (list->data == nullptr) {
        // Return error code: if list not empty, -6 (0xFFFFFFFA) + 0x271E = 0x2718, else 0x271E?
        return (list->count != 0) ? 0x2718 : 0x271E;
    }

    // Write itemId and itemValue at the next slot (at offset count*0xC4)
    *((short*)((uintptr_t)list->data + list->count * 0xC4)) = itemId;
    *((short*)((uintptr_t)list->data + list->count * 0xC4 + 2)) = itemValue;

    // Point to the new entry
    newEntry = (InventoryEntry*)((uintptr_t)list->data + list->count * 0xC4);

    // Copy UI-related data from this object to some UI component
    *((short*)(*((int*)(this + 0x180)) + 0x60)) = *((short*)(list + 0x1e28));
    *((short*)(*((int*)(this + 0x180)) + 0x62)) = *((short*)(list + 0x1e2a));

    FUN_00674e10(); // Unknown function, possibly UI update

    // Copy default name from this object
    char* srcName = *(char**)(this + 0x50);
    dstName = newEntry->name;
    if (srcName == nullptr) {
        *dstName = '\0';
    } else {
        int i = 0;
        for (i = 0; i < 64; i++) {
            if (srcName[i] == '\0') break;
            dstName[i] = srcName[i];
        }
        dstName[i] = '\0';
    }

    // Copy default stats from this object (short array, null-terminated)
    srcStats = *(short**)(this + 0x54);
    dstStats = &newEntry->stats[0];
    if (srcStats == nullptr) {
        *dstStats = 0;
    } else {
        statIdx = 0;
        if (*srcStats != 0) {
            do {
                if (statIdx > 127) break;  // safety limit (but array size is 64, potential bug)
                dstStats[statIdx] = srcStats[statIdx];
                statIdx++;
            } while (srcStats[statIdx] != 0);
        }
        dstStats[statIdx] = 0;
    }

    // If both name and stats are empty, generate a default name from the slot index
    if ((newEntry->name[0] == '\0') && (newEntry->stats[0] == 0)) {
        _sprintf(newEntry->name, "%d", (unsigned int)list->count);
    }

    // Increment list count
    list->count++;

    return 0;
}