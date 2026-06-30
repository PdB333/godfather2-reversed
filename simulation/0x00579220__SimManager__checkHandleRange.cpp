// FUNC_NAME: SimManager::checkHandleRange
// Function address: 0x00579220
// This function checks if a handle (object ID) falls within a given range [rangeStart, rangeEnd).
// Returns the handle value with bit 0 set if found within the range (i.e., active), else cleared.
// The handle is stored at this+0x60. If not matching, it iterates through the object pool array
// (offset 0x2ec, stride 0xe0) using a two‑level indexing scheme defined by members at +0x2e4 and +0x2e8.

uint __thiscall SimManager::checkHandleRange(uint rangeStart, uint rangeEnd)
{
    uint selfId = *(uint *)(this + 0x60); // +0x60: object's own handle ID
    // Quick check: is our own ID already in range?
    if ((rangeStart <= selfId) && (selfId < rangeEnd))
    {
        return (selfId & 0xFFFFFF00) | 1; // mark as found
    }

    // Get total number of objects to check (e.g., active count)
    uint objectCount = getObjectCount(); // FUN_00579170, likely this->m_objectCount
    int index = 0;
    uint result = objectCount; // will be modified in loop if needed

    if ((int)objectCount > 0)
    {
        int blockSize = *(int *)(this + 0x2e4);   // +0x2e4: number of slots per block (divisor)
        int totalElements = *(int *)(this + 0x2e8); // +0x2e8: base offset (maybe total objects)
        int currentSlot = totalElements + blockSize; // start from the end of the block

        do
        {
            // Compute block number (quotient) and index within block (remainder)
            int blockIndex = currentSlot / blockSize;
            int slotIndex = currentSlot % blockSize;

            // Read handle from object at slotIndex (stride 0xe0 bytes, handle at offset +0x60)
            uint objId = *(uint *)(slotIndex * 0xe0 + *(int *)(this + 0x2ec) + 0x60);

            if ((rangeStart <= objId) && (objId < rangeEnd))
            {
                // Found: return the block index (or whatever blockIndex represents) with found flag
                return (blockIndex & 0xFFFFFF00) | 1;
            }

            index++;
            currentSlot--;
        } while (index < (int)objectCount);

        result = objectCount; // fallback to objectCount with low byte cleared
    }

    return result & 0xFFFFFF00; // not found, clear low byte flag
}