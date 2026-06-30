// FUN_004c34d0: ConfigParser::parseAddEntry

// Structure for a parsed entry (12 bytes)
struct ConfigEntry {
    uint32_t type;         // +0x00: e.g., 0xfe16702f or parsed hex
    void*   payload;       // +0x04: additional data (pointer)
    int*    refCounter;    // +0x08: shared reference counter
};

// Member fields of ConfigParser (offsets relative to this)
// +0x208: ConfigEntry** m_entries          (dynamic array of pointers)
// +0x20c: int            m_numEntries
// +0x210: int            m_capacity

void __thiscall ConfigParser::parseAddEntry(int* refCounterOut, const char* tokenizedString)
{
    // Decomposed: this = param_1, refCounterOut = param_2, tokenizedString = param_3

    // Delimiters for strtok (loaded from globals)
    char delimiters[2];
    delimiters[0] = DAT_00e3621c;   // likely newline or space
    delimiters[1] = DAT_00e3621e;

    int entryCount = 0xffffffff;    // default sentinel
    uint32_t parsedType = 0xfe16702f;   // default "empty" type
    void* parsedPayload = nullptr;

    // First token: number of entries to follow
    char* token = strtok(tokenizedString, delimiters);
    sscanf(token, "%d\n", &entryCount);

    // Reset tokenizedString for subsequent calls
    tokenizedString = nullptr;

    if (entryCount != 0) {
        // Second token: hex type (e.g., "0x12345678")
        token = strtok(nullptr, delimiters);
        sscanf(token, "0x%x", &parsedType);

        // Third token: optional payload (if count > 1)
        if (entryCount > 1) {
            token = strtok(nullptr, delimiters);
            sscanf(token, "0x%x", &parsedPayload);
        }
    }

    // Allocate a new ConfigEntry on the heap
    ConfigEntry* newEntry = (ConfigEntry*)FUN_009c8e50(12); // likely operator new or custom allocator
    if (newEntry != nullptr) {
        newEntry->type = 0xfe16702f;        // set default
        newEntry->payload = nullptr;
        newEntry->refCounter = refCounterOut;
        (*refCounterOut)++;                 // increment shared counter
    }

    // Override with actual parsed values
    newEntry->type = parsedType;
    newEntry->payload = parsedPayload;

    // Check if dynamic array needs resizing
    if (m_numEntries == m_capacity) {
        int newCapacity = (m_capacity == 0) ? 1 : (m_capacity * 2);
        FUN_004c37e0(newCapacity);  // reallocates m_entries array
    }

    // Add the new entry pointer to the array
    ConfigEntry** slot = &m_entries[m_numEntries]; // m_entries + m_numEntries * sizeof(pointer)
    m_numEntries++;
    if (slot != nullptr) {
        *slot = newEntry;
    }
}