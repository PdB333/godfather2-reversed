// FUNC_NAME: GhostSlotManager::remapOrClearSlots
void GhostSlotManager::remapOrClearSlots()
{
    // Offset 0x0C: flag indicating whether to clear (non-zero) or remap (zero)
    bool bClearMode = *(char*)(this + 0x0C) != 0;
    int count = *(int*)(this + 0x08);            // Offset 0x08: number of slots
    int* pArrayBase = *(int**)(this + 0x04);     // Offset 0x04: pointer to slot array (each slot is 0x20 bytes)
    int* remapTable = (int*)(this + 0x18);       // Offset 0x18: inline remap table (array of ints)

    for (int i = 0; i < count; i++)
    {
        // Each slot has a 4-byte field at offset 0x1C within the 0x20-byte slot
        int* slotField = (int*)(pArrayBase + 0x1C/sizeof(int) + i * (0x20/sizeof(int)));

        if (!bClearMode)
        {
            // Remap: read current value, use it as index into remapTable, write back
            *slotField = remapTable[*slotField];
        }
        else
        {
            // Clear: zero out the field
            *slotField = 0;
        }
    }
}