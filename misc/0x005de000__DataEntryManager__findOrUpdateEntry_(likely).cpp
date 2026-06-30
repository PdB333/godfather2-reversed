// FUNC_NAME: DataEntryManager::findOrUpdateEntry (likely)
// Address: 0x005de000
// Role: Searches for an existing entry by (id1, id2). If found, updates currentValue and previousValue.
// If not found, allocates a new entry from the global pool, initializes it with the given data,
// and appends it to the internal array (max 20 entries). Returns 1 on success, 0 on failure.

#include <cstdint>

// Forward declarations of helper functions (probably from the same module)
uint32_t* poolAllocateMore(); // 0x004de190
void entryConstructor(uint32_t* entry); // 0x005dd030
void resizeEntryArray(uint32_t newCapacity); // 0x005e1c00

// Global pool allocator singleton (address 0x01223508)
struct PoolAllocator {
    uint32_t field_0x00;        // unknown
    // ...
    uint32_t unusedCount;       // +0x1c (decremented when popped)
    uint32_t usedCount;         // +0x20 (incremented when popped)
    uint32_t flags;             // +0x34 (bit 0 check)
    uint32_t someCondition;     // +0x40 (probably null check)
    uint32_t* freeListHead;     // +0x44 (linked list of free entries)
};

extern PoolAllocator* g_poolAllocator; // DAT_01223508

// Entry data structure (size at least 0x68)
struct EntryData {
    // Sentinels (set after allocation)
    uint32_t magic1;   // +0x10 : 0xbadbadba
    uint32_t magic2;   // +0x14 : 0xbeefbeef
    uint32_t magic3;   // +0x18 : 0xeac15a55
    uint32_t magic4;   // +0x1c : 0x91100911
    // Padding ?
    uint32_t field_0x50;   // +0x50 : from inputStruct[0x4]
    uint32_t id1;          // +0x54 : from inputStruct[0x8]
    uint32_t id2;          // +0x58 : from inputStruct[0xc]
    uint32_t field_0x5c;   // +0x5c : from inputStruct[0x10]
    uint32_t currentValue; // +0x60 : from inputStruct[0x14] (updated on match)
    uint32_t previousValue;// +0x64 : from inputStruct[0x14] (updated on match)
};

// Input structure for findOrUpdateEntry
struct InputData {
    uint32_t something;     // +0x00? Not used in this function?
    uint32_t field_0x04;    // stored at +0x50 of entry
    uint32_t id1;           // +0x08
    uint32_t id2;           // +0x0c
    uint32_t field_0x10;    // stored at +0x5c of entry
    uint32_t value;         // +0x14 (stored at both +0x60 and +0x64)
};

class DataEntryManager {
public:
    EntryData** m_entries;      // +0x270
    uint32_t m_entryCount;      // +0x274
    uint32_t m_capacity;        // +0x278

    // __thiscall method (param_1 = this, param_2 = pointer to InputData)
    uint32_t findOrUpdateEntry(const InputData* input);
};

uint32_t DataEntryManager::findOrUpdateEntry(const InputData* input) {
    // First, try to find an existing entry with matching (id1, id2)
    uint32_t index = 0;
    if (m_entryCount != 0) {
        EntryData** current = m_entries;
        do {
            EntryData* entry = *current;
            if (entry != nullptr &&
                entry->id2 == input->id2 &&
                entry->id1 == input->id1) {
                // Update the entry with the new value (store as both previous and current)
                entry->previousValue = input->value;
                entry->currentValue = input->value;
                // Return success handle with index encoded (but index is small, so low byte=1)
                return (index >> 8) << 8 | 0x01;
            }
            index++;
            current++;
        } while (index < m_entryCount);
    }

    // If no match, try to create a new entry from the global pool
    if (g_poolAllocator->someCondition == 0 &&
        (g_poolAllocator->someCondition2 == 0 || (g_poolAllocator->flags & 1) == 0)) {
        // Pool might need initialization; call the allocation function (may set up pool)
        poolAllocateMore();
    }

    uint32_t* newEntry = g_poolAllocator->freeListHead;
    if (newEntry != nullptr) {
        // Pop from free list
        uint32_t nextFree = *newEntry; // free list is singly linked
        g_poolAllocator->usedCount++;
        g_poolAllocator->unusedCount--;
        g_poolAllocator->freeListHead = reinterpret_cast<uint32_t*>(nextFree);

        // Set sentinel values for debugging
        newEntry[4] = 0xbadbadba;
        newEntry[5] = 0xbeefbeef;
        newEntry[6] = 0xeac15a55;
        newEntry[7] = 0x91100911;

        // Call the entry constructor (probably does more initialization)
        entryConstructor(newEntry);

        // Copy fields from input structure to the new entry
        newEntry[0x14] = input->field_0x04;   // offset 0x50
        newEntry[0x15] = input->id1;          // offset 0x54
        newEntry[0x16] = input->id2;          // offset 0x58
        newEntry[0x17] = input->field_0x10;   // offset 0x5c
        newEntry[0x19] = input->value;        // offset 0x64 (previousValue)
        newEntry[0x18] = input->value;        // offset 0x60 (currentValue)

        // Add to the internal array (max 20 entries)
        if (m_entryCount < 20) {
            // Ensure capacity (grow if needed)
            if (m_entryCount == m_capacity) {
                uint32_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
                resizeEntryArray(newCapacity);
            }

            // Append the new entry pointer
            EntryData** appendSlot = m_entries + m_entryCount;
            *appendSlot = reinterpret_cast<EntryData*>(newEntry);
            m_entryCount++;

            // Return success with count encoded (but count is small, so low byte=1)
            return (m_entryCount >> 8) << 8 | 0x01;
        }
        // If array already full, we still popped from pool but couldn't add? Return failure? The code returns
        // nextFree & 0xffffff00, which might be error indicator. We treat as 0.
        return 0;
    }

    // Pool empty or other failure
    return 0;
}