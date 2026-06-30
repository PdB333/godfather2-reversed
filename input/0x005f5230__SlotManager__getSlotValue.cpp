//FUNC_NAME: SlotManager::getSlotValue
// Function address: 0x005f5230
// Searches for a slot by ID in an array of 10 slots, retrieves a value from the corresponding data entry.
// If the entry is in a special state (iVar2 == 1), returns 0 and sets output to -1.
// Otherwise, returns 1 with the value from offset 0x100.
// Note: The scaling logic (ratio of index to count) appears to be dead code due to a condition that is never true.

// Structure for a slot entry (size 0x5C)
struct SlotEntry {
    int id;          // +0x00: unique identifier
    char pad[0x58];  // +0x04 to +0x5B
};

// Structure for a data entry (size 0x170)
struct DataEntry {
    char pad0[0x88]; // +0x00 to +0x87
    int count;       // +0x88: some count (iVar1)
    int index;       // +0x8C: index or progress (iVar4)
    char pad1[0x14]; // +0x90 to +0xA3
    int state;       // +0xA4: state flag (iVar2)
    char pad2[0x58]; // +0xA8 to +0xFF
    int value;       // +0x100: the value to retrieve
    // remaining 0x70 bytes
};

// Global constants (from data references)
static float g_scaleFactor = 1.0f; // DAT_00e2af48 (cancels out in ratio)
static float g_negativeAdjust = 0.5f; // DAT_00e44578 (added to negative values before rounding)

int __thiscall SlotManager::getSlotValue(int thisPtr, int targetId, int* outValue)
{
    int i;
    SlotEntry* slotArray = (SlotEntry*)(thisPtr + 0x82B0);
    DataEntry* dataArray = (DataEntry*)(thisPtr + 0x8210);

    // Search for slot with matching ID
    for (i = 0; i < 10; i++) {
        if (slotArray[i].id >= 0 && slotArray[i].id == targetId) {
            break;
        }
    }
    if (i >= 10) {
        return 0; // not found
    }

    // Lock (simulated)
    FUN_00ab4db0(&DAT_00e2aea0);

    // Retrieve value from corresponding data entry
    DataEntry* entry = &dataArray[i];
    *outValue = entry->value;

    int count = entry->count;   // +0x88
    int index = entry->index;   // +0x8C
    int state = entry->state;   // +0xA4

    // Unlock
    FUN_00ab4e70();

    if (state != 1) {
        // Attempt to scale value by ratio of index to count (dead code due to condition)
        if (count > 0) {
            float ratio = ((float)index * g_scaleFactor) / ((float)count * g_scaleFactor);
            if (ratio < 0.0f) { // This condition is never true (ratio >= 0)
                float temp = (float)*outValue;
                if (*outValue < 0) {
                    temp += g_negativeAdjust;
                }
                *outValue = (int)(temp * ratio + 0.5f); // ROUND
            }
        }
        return 1;
    }

    // State == 1: invalid entry
    *outValue = -1;
    return 0;
}