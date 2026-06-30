// FUNC_NAME: ObjectSlotManager::findEmptySlot
// Address: 0x00427f70
// This function manages a global pool of 512 slots (0x200). It either validates an existing slot index (if < 0x200) or searches for a new free slot.
// The global array DAT_012083e8 is an array of SlotInfo structures (each 16 bytes). The first int (offset 0) is the slot's owner ID (0 = free), the fourth int (offset 12) indicates the slot is allocated (non-zero = present).
// A global counter DAT_01163cbc is incremented when a slot is confirmed as allocated (e.g., a duplicate or reference count).

struct SlotInfo {
    int ownerID;        // +0x00: 0 = free, >0 = assigned owner
    int field4;         // +0x04: unknown
    int field8;         // +0x08: unknown
    int allocatedFlag;  // +0x0C: non-zero = slot is in use
};

// Global variables
SlotInfo g_slotPool[0x200];  // DAT_012083e8
int g_allocatedCount;         // _DAT_01163cbc

// External function called after slot assignment
bool validateSlotAssignment(); // FUN_00427d20

int __thiscall ObjectSlotManager::findEmptySlot(void)
{
    // 'this' holds the current slot index at offset 0x28
    unsigned int currentSlot = *(unsigned int*)((char*)this + 0x28);

    // If we already have a slot index that is within range (0..0x1FF), verify it is still valid
    if (currentSlot < 0x200) {
        SlotInfo* pool = g_slotPool;
        SlotInfo* entry = &pool[currentSlot];
        // If the slot's allocatedFlag is non-zero and equals 1 (meaning it was previously allocated),
        // increment the global counter and return success
        if (entry->allocatedFlag != 0 && entry->allocatedFlag == 1) {
            g_allocatedCount++;
        }
        return 1; // slot index is valid
    }

    // Otherwise, search for a free slot in the pool
    unsigned int i = 0;
    SlotInfo* ptr = g_slotPool;
    // Continue while the slot is not free: skip if allocatedFlag == 0 OR ownerID != 0
    while (ptr->allocatedFlag == 0 || ptr->ownerID != 0) {
        i++;
        ptr++;
        if (i > 0x1FF) {
            return 0; // no free slot available
        }
    }

    // Found free slot at index i
    if (i > 0x1FF) {
        return 0; // sanity check (should never happen)
    }

    // Assign this slot index to the object
    *(unsigned int*)((char*)this + 0x28) = i;

    // Validate the assignment; if it fails, reset slot index to -1
    bool valid = validateSlotAssignment();
    if (!valid) {
        *(int*)((char*)this + 0x28) = -1;
    }

    return 1;
}