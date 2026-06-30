// FUNC_NAME: MemoryPool::releaseEntry
void __thiscall MemoryPool::releaseEntry(char shouldMark)
{
    int slotIndex;
    Entry* entry;

    // m_count is the number of allocated entries (or next slot index)
    if (m_count != 0 && shouldMark != '\0') {
        // Mark the slot at (m_count-1) as used in the usage mask
        m_usageMask |= 1 << ((m_count - 1) & 0x1F);
    }

    // Retrieve the entry pointer from the entries array at offset (m_count + 2)
    // The entries array starts at m_entries (offset +8), each element is a pointer to an Entry struct.
    entry = m_entries[m_count];  // m_entries is at base +8, so m_entries[m_count] equivalent to base[m_count+2]
    m_count++;

    // Zero out the entry's data buffer
    if (entry->size != 0) {
        for (unsigned int i = 0; i < entry->size; i++) {
            ((char*)entry->data)[i] = 0;
        }
    }
}