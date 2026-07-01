// FUNC_NAME: CIdAllocator::validateSlotUnoccupied
// Address: 0x00949ee0
// Role: Validates that no existing chunk in the sorted array starts within a specific ID range.
// The chunk array is at `m_pChunks` (+0x60), each entry is 8 bytes (first uint = rangeStart, second unused here).
// `m_chunkCount` at +0x64 stores the number of chunks.
// `param_2` defines a slot: slotID * 10000 to (slotID+1)*10000.
// The function returns early if any chunk's rangeStart is >= upper bound or if it's not the first two IDs of the slot.
// This suggests the slot reservation expects exactly one chunk at either slot_base or slot_base+1.

void __thiscall CIdAllocator::validateSlotUnoccupied(int slotID)
{
    uint upperBound = slotID * 10000;                 // +0x0: lower bound (not used)
    uint lowerBound = slotID * 10000;                 // reuse slotID*10000
    uint currentBound = lowerBound + 1;               // start at lower+1 for comparison
    uint idx = 0;                                      // loop counter

    // If there are no chunks, nothing to validate
    if (this->m_chunkCount == 0) {
        return;
    }

    // Pointer to the first chunk's rangeStart (offset +4 to skip a possible header)
    uint* pRangeStart = (uint*)(*(int*)(this + 0x60) + 4);

    do {
        uint val = *pRangeStart;                       // first uint of current chunk

        // If val >= (slotID+1)*10000, all remaining chunks are beyond this slot
        if (lowerBound + 10000 <= val) {
            return;
        }

        // If val is within the slot, only allow val == slotID*10000 or slotID*10000+1
        if (lowerBound <= val) {
            if (currentBound < val) {
                return;                                // val > slotID*10000+1 → not allowed
            }
            // val is exactly lowerBound or lowerBound+1 → increment local var (no effect)
            currentBound = currentBound + 1;
        }

        idx = idx + 1;
        pRangeStart = pRangeStart + 2;                 // advance 8 bytes to next chunk
    } while (idx < this->m_chunkCount);
}