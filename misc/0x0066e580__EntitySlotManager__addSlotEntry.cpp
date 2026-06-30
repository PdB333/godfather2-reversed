// FUNC_NAME: EntitySlotManager::addSlotEntry
// Function address: 0x0066e580
// This function adds an item (param) into a slot-based managed collection.
// It uses a sequential slot index (m_nextSlotIndex) and stores the item pointer
// in both a simple array (m_slotEntries) and a computed slot block address
// (m_slotBlockOffsets). The block address is derived from a fixed base
// (this + 0x4ad10) plus an offset determined by m_currentSlotType * 0xa0.
void __thiscall EntitySlotManager::addSlotEntry(void* param)
{
    // +0x18: store item pointer (possibly owner/back-reference)
    this->m_owner = param;

    // +0x49d08, 0x49d0a: sequential slot index management
    unsigned short slotIndex = this->m_nextSlotIndex;   // +0x49d0a
    this->m_previousSlotIndex = slotIndex;               // +0x49d08
    this->m_nextSlotIndex = slotIndex + 1;                // +0x49d0a

    // +0x49d00: last added item
    this->m_lastAdded = param;

    // +0x49d10: array of pointers indexed by slotIndex
    this->m_slotEntries[slotIndex] = param;

    // +0x4a510: array of unsigned ints (block addresses) indexed by slotIndex
    // Compute address of the slot block identified by m_currentSlotType (+0x49d04)
    unsigned int blockAddr = reinterpret_cast<unsigned int>(this) + 0x4ad10
                           + (this->m_currentSlotType * 0xa0);
    this->m_slotBlockOffsets[slotIndex] = blockAddr;
}