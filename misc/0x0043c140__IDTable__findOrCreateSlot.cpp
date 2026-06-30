// FUNC_NAME: IDTable::findOrCreateSlot
// Address: 0x0043c140
// This function searches a table of 64 slots (each 28 bytes) for a given ID.
// If found, it optionally increments a reference count (offset +0x04 within slot).
// If not found, it allocates the first empty slot (first int == -1) and sets its ID.
// Returns the slot index (0-63) or 0xFFFFFFFF if table is full and ID not found.

uint IDTable::findOrCreateSlot(int id, char incrementRef)
{
    uint firstFree = 0xFFFFFFFF;
    uint foundSlot = 0xFFFFFFFF;
    uint i = 0;
    int* slotArray = *(int**)(this + 0x04); // array of 64 slots, each 7 ints (28 bytes)

    do {
        if (*slotArray == -1) {
            // Slot is empty; remember first free slot if not already set
            if (firstFree == 0xFFFFFFFF) {
                firstFree = i;
            }
        }
        else if (*slotArray == id) {
            foundSlot = i;
            if (i != 0xFFFFFFFF) goto LAB_0043c195;
            break;
        }
        i++;
        slotArray += 7; // move to next slot (7 ints per slot)
    } while (i < 0x40);

    // If a free slot was found and we didn't already find the ID, use it
    i = firstFree;
    if (i != 0xFFFFFFFF) {
        (*(int**)(this + 0x04))[i * 7] = id; // set ID in the new slot
    }

LAB_0043c195:
    foundSlot = i;
    if (incrementRef != '\0') {
        // Increment reference count at slot offset +0x04 (second int)
        int* refCountPtr = (int*)(*(int*)(this + 0x04) + 4 + i * 0x1C);
        *refCountPtr = *refCountPtr + 1;
    }
    return foundSlot;
}