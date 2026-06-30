// FUNC_NAME: GhostList::searchByID
int GhostList::searchByID(uint32_t key) {
    int low = -1;
    int high = m_count;               // +0x04: number of entries
    int result = -1;
    if (m_count != 0) {
        do {
            int mid = (low + high) >> 1;
            // Each entry is 8 bytes; compare only the first 4-byte key
            uint32_t entryKey = m_pArray[mid].key; // +0x00: key field in 8-byte structure
            if (entryKey < key) {
                low = mid;
            } else {
                high = mid;
            }
        } while (low + 1 != high);
        if (high < m_count && m_pArray[high].key == key) {
            result = high;
        }
    }
    return result; // -1 if not found
}