// FUNC_NAME: HashTable::setEntryValue
// Address: 0x00477cd0
// This function looks up or creates an entry in a hash table (identified by key 0x8c207d80),
// then sets the entry's value field (at offset 12) to the object's stored value at this+0x84.
// The hash table is stored at this+0x20. The entry type field is at offset 0; value 4 indicates existing entry.
void HashTable::setEntryValue() {
    // Offset to hash table pointer
    // +0x20: m_hashTablePtr (pointer to hash table structure)
    int* entry = (int*)hashFind(this->m_hashTablePtr, 0x8c207d80, -1);
    if (entry != nullptr) {
        // If entry type is 4, skip removal and reuse it
        if (*entry == 4)
            goto LABEL_SET;
        // Remove existing entry with this key before adding a new one
        hashRemove(0x8c207d80);
    }
    // Add new entry of type 4
    entry = (int*)hashAdd(4, this->m_hashTablePtr, 0x8c207d80, -1);

LABEL_SET:
    // Advance to the value field (offset 12 bytes = 3 ints)
    entry += 3;
    // Set value (first zero, then overwritten with stored value)
    *entry = 0;
    *entry = *(int*)((char*)this + 0x84); // +0x84: m_storedValue
}