// FUNC_NAME: CEntryManager::getEntryId
// Address: 0x00602f00
// Role: Retrieves a composite identifier for an entry by index. If index == 0xFFFFFFFF, uses stored default index. Returns a 32-bit value formed from the entry's address (shifted right 8) and a byte at offset 0x60 within the entry.
// Structure at this:
//   +0x20: m_pArrayDescriptor (pointer to ArrayDescriptor)
//   +0x3c: m_defaultIndex (uint)
// ArrayDescriptor:
//   +0xa4: m_count (uint)
//   +0xac: m_pData (pointer to array of entries, each 0x61 bytes)
// Entry:
//   +0x60: m_flag (uint8)

unsigned int __thiscall getEntryId(unsigned int index) {
    unsigned int actualIndex;
    int entryBase;

    // Use default index if caller passed 0xFFFFFFFF
    if (index == 0xFFFFFFFF) {
        actualIndex = this->m_defaultIndex; // +0x3c
    } else {
        actualIndex = index;
    }

    // Bounds check against array count
    if (actualIndex < this->m_pArrayDescriptor->m_count) { // +0x20->+0xa4
        // Compute pointer to the start of the entry
        entryBase = actualIndex * 0x61 + this->m_pArrayDescriptor->m_pData; // +0x20->+0xac

        // Build return value:
        //   high 24 bits = (entryBase >> 8) & 0xFFFFFF
        //   low  8 bits = byte at offset 0x60 within the entry
        return ((entryBase >> 8) & 0xFFFFFF) << 8 | *(unsigned char *)(entryBase + 0x60);
    } else {
        // Out of bounds: return a fixed error identifier
        // Uses DAT_012222c0 (a static byte from address 0x012222c0)
        return (0x012222 << 8) | DAT_012222c0;
    }
}