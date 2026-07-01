// FUNC_NAME: HashTable::FindOccupiedSlot
uint HashTable::FindOccupiedSlot(HashTable *this, uint unusedKey, uint *outEntry)
{
    // Structure: +0x00 m_entries (pointer to uint array), +0x04 m_count (number of slots)
    uint count = this->m_count; // param_1[1]
    uint idx = Sub_006EB670(count); // initial probe index derived from count (possibly hash of key, but key is unused)
    uint probes = 0;

    if (count == 0) {
        return 0xFFFFFFFF; // empty table
    }

    do {
        uint entry = this->m_entries[idx]; // *(undefined4 *)(*param_1 + idx * 4)
        if (Sub_0078F040(entry) != 0) { // predicate: returns true if slot is occupied/matching condition
            *outEntry = entry;
            return idx; // found
        }
        idx = (idx + 1) % count; // linear probe, wrap around
        probes++;
    } while (probes < count); // full scan

    return 0xFFFFFFFF; // not found
}