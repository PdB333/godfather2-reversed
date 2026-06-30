// FUNC_NAME: StringDataTable::registerString
// Address: 0x00616b20
// Role: Looks up a string in a global hash table, creates if not found, then associates it with each element of an array attached to the calling object.

// Assumed class layout (offsets relative to this):
// +0x00: char* m_string          (pointer to the string to register)
// +0x04: uint32_t m_paddingOrLen (unused here, but might hold string length or hash)
// +0x06: uint16_t m_count        (number of entries in the data array)
// +0x08: uint16_t padding
// +0x0C: uint8_t (*m_dataArray)[0x18]  (array of structures, each 0x18 bytes)
uint32_t StringDataTable::registerString()
{
    char c;
    char *pChar;
    char *pStr;
    uint32_t hashValue;
    int hashEntry;
    uint16_t i;

    // Acquire a lock (likely a mutex or critical section)
    acquireLock(); // FUN_0061c350

    pStr = this->m_string;  // *in_EAX
    pChar = pStr;
    do {
        c = *pChar;
        pChar++;
    } while (c != '\0');
    // Compute hash of the string (length = pChar - pStr - 1, but hash function takes the string and length)
    // FUN_00ab8560(uint32_t seed, const char* str, int len)
    hashValue = hashString(0, pStr, (int)(pChar - pStr - 1));  // actually pChar-1 points to null, so length = pChar - pStr - 1? The decompiled: (int)pcVar3 - (int)(pcVar2 + 1) = pChar - (pStr+1) = length excluding null
    // Hash table is global at DAT_01205968, an array of pointers (bucket heads)
    hashEntry = *(int *)(DAT_01205968 + (hashValue & 0x1FF) * 4);
    // Walk the linked list to find matching entry by full hash
    while (hashEntry != 0 && *(uint32_t *)(hashEntry + 4) != hashValue) {
        hashEntry = *(int *)(hashEntry + 8);
    }

    if (hashEntry == 0) {
        // Not found, create a new hash table entry
        hashEntry = createHashEntry(hashValue); // FUN_00616590
    }

    // Now associate the string with each element in the object's data array
    for (i = 0; i < this->m_count; i++) {
        // FUN_00616a60(void* hashEntry, void* dataElement, int unknownFlag=1)
        // This likely adds a reference from the data element to the string entry
        addDataLink(hashEntry, this->m_dataArray + i * 0x18, 1);
    }

    // Return the hash value (which is stored in the hash entry at offset +4)
    return *(uint32_t *)(hashEntry + 4);
}