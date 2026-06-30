// FUN_00505c90: FixedSlotTable::FindOrCreateSlot
// This function manages a small fixed-size array of 4 slots (each 0x14 bytes) starting at offset 0x40.
// It searches for a slot with a matching ID (passed via EDI) and returns a pointer to the slot.
// If not found, it allocates the first empty slot (ID == 0) and sets its ID to the requested one.
// If no empty slot is found, it overwrites the last visited empty slot? But the original code uses iVar3 which is the last empty index found.

int __thiscall FixedSlotTable::FindOrCreateSlot(int this, int id) // id passed in EDI (unaff_EDI)
{
    int emptyIndex = 0;
    for (int i = 0; i < 4; i++)
    {
        // Each slot has its ID at offset 4 from the slot base (array base is at this+0x40)
        int slotId = *(int *)(this + 0x44 + i * 0x14);
        if (slotId == id)
        {
            // Found matching slot, return pointer to its base (offset 0x40 + i*0x14)
            return (int)(this + 0x40 + i * 0x14);
        }
        if (slotId == 0)
        {
            emptyIndex = i;
        }
    }
    // No match found; take the last empty slot (or the zeroth if none empty)
    int *slotIdPtr = (int *)(this + 0x44 + emptyIndex * 0x14);
    *slotIdPtr = id;
    return (int)(this + 0x40 + emptyIndex * 0x14);
}