// FUNC_NAME: CEntryList::resetEntries
void CEntryList::resetEntries() {
    int count = this->m_entryCount;         // +0x654
    if (count > 0) {
        Entry* entry = reinterpret_cast<Entry*>(this + 0x658); // +0x658, 8-byte entries
        for (int i = 0; i < count; i++) {
            clearEntry(entry);               // FUN_00459280 – release/reset single entry
            entry++;
        }
    }
    this->m_entryCount = 0;                  // +0x654 set to zero
}