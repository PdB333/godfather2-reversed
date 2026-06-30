// FUNC_NAME: HandleManager::allocateHandle

void __thiscall HandleManager::allocateHandle(uint32_t& outIndex)
{
    uint32_t currentCount = *(uint32_t*)(this + 0x38);     // m_count
    uint32_t idx = 0;

    // Search for a free slot (first uint32 == 0 means unused)
    if (currentCount != 0)
    {
        Slot* slots = *(Slot**)(this + 0x34);              // m_pSlots
        do
        {
            if (slots[idx].m_inUse == 0)
            {
                slots[idx].m_inUse = 1;
                outIndex = idx;
                return;
            }
            idx++;
        } while (idx < currentCount);
    }

    // No free slot found – use a new slot at the end
    outIndex = currentCount;

    uint32_t capacity = *(uint32_t*)(this + 0x3c);         // m_capacity
    if (currentCount == capacity)
    {
        // Grow the table if currently full
        uint32_t newCapacity = (capacity != 0) ? (capacity * 2) : 1;
        FUN_00455500(newCapacity);                         // growTable(newCapacity)
    }

    // Initialize the new slot (index = old currentCount)
    Slot* newSlot = *(Slot**)(this + 0x34) + currentCount; // m_pSlots[currentCount]
    if (newSlot != nullptr)
    {
        newSlot->m_inUse = 0;
        newSlot->m_magic = 0xFE16702F;                     // magic cookie or handle generation
        newSlot->m_data  = 0;
    }

    *(uint32_t*)(this + 0x38) = currentCount + 1;          // increment m_count
    (*(Slot**)(this + 0x34))[outIndex].m_inUse = 1;        // mark the returned slot as used
}