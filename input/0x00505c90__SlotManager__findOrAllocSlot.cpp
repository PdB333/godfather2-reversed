// FUNC_NAME: SlotManager::findOrAllocSlot
int* SlotManager::findOrAllocSlot(int slotId)
{
    int* foundIndex = 0;    // index of empty slot found (if any)
    int i;

    // Search through the 4 slots (each 0x14 bytes, ID field at +0x04)
    int* idField = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x44); // points to first slot's ID field
    for (i = 0; i < 4; i++)
    {
        if (*idField == slotId)
        {
            // Slot already occupied by this ID; return pointer to its base
            return reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x40 + i * 0x14);
        }
        if (*idField == 0)
        {
            // Record first empty slot index
            foundIndex = i;
        }
        idField += 5; // advance 5 ints (0x14 bytes) to next slot's ID field
    }

    // No matching slot found; use the first empty slot (foundIndex)
    int* slotBase = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x40 + foundIndex * 0x14);
    // Set the ID field at offset +0x04 to the given slotId
    *(slotBase + 1) = slotId; // (slotBase + 1) is at offset 4 bytes from slotBase
    // Return pointer to the base of this slot
    return slotBase;
}