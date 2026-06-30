// FUNC_NAME: FreeSlotPool::popFreeSlot
// Address: 0x005e48d0
// This function pops a free slot from a pool and relocates the last entry to the front.
// The pool stores 64-bit entries (2 uint32_t values) in a contiguous array.
// Offsets:
//   +0x6030: m_freeSlotCount (int) - number of free slots available
//   +0x602c: m_freeSlotData (uint32_t*) - pointer to the array of slot entries (each entry = 2 uint32_t)
// On success, returns (m_freeSlotData & 0xFFFFFF00) | 1; on failure (no slots), returns defaultReturn.
// The low byte of the return value is 1 if a slot was popped, else 0.

uint __fastcall FreeSlotPool::popFreeSlot(void* this, uint defaultReturn)
{
    int slotCount;
    uint32_t* basePtr;
    uint result;

    slotCount = *(int*)((char*)this + 0x6030);  // +0x6030: m_freeSlotCount
    result = defaultReturn & 0xffffff00;

    if (slotCount != 0)
    {
        // If more than one slot exists, copy the last entry to the front (index 0)
        if (slotCount > 1)
        {
            basePtr = *(uint32_t**)((char*)this + 0x602c);  // +0x602c: m_freeSlotData
            // Move the last entry (at index slotCount-1) to the first entry (index 0)
            basePtr[0] = basePtr[(slotCount - 1) * 2];      // first word of last entry
            basePtr[1] = basePtr[(slotCount - 1) * 2 + 1]; // second word of last entry
        }

        // Decrement the count (effectively remove the last slot)
        *(int*)((char*)this + 0x6030) = slotCount - 1;

        // Build return value: low byte = 1 (success), high 24 bits = top bits of m_freeSlotData
        basePtr = *(uint32_t**)((char*)this + 0x602c);
        result = ((uint)basePtr & 0xffffff00) | 1;
    }

    return result;
}