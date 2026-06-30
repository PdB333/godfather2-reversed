// FUNC_NAME: GlobalKeyedTable::insert
// Purpose: Insert a 16-byte key into a global table if not already present.
// Returns: Pointer to associated 8-byte value area if newly added; NULL if key already exists.
// The global table is stored as an array of 24-byte entries (16-byte key + 8-byte value).
// Table pointer and count are in the global variable gKeyedTable (DAT_012054c0).

#include <cstdint>

// Global table metadata: pointer to entry array, and count of entries.
// In original code: DAT_012054c0[0] = entry array pointer, DAT_012054c0[1] = count.
struct KeyedTable {
    uint32_t* entries; // array of entries, each entry is 6 uint32_t
    int count;
};

extern KeyedTable gKeyedTable; // at 0x012054c0

// Forward declaration of allocator (FUN_004e17b0) assumed to allocate memory for one entry (6 uint32_t)
extern uint32_t* allocateTableEntry(); // returns pointer to a new 24-byte block

// The key is a struct of 4 uint32_t; value is a struct of 2 uint32_t (or uint64_t)
struct Key128 {
    uint32_t dwords[4];
};

struct Value64 {
    uint32_t dwords[2];
};

struct Entry {
    Key128 key;   // offsets 0-15
    Value64 value; // offsets 16-23
};

// The function takes a pointer to a Key128 (in ESI) and checks for existence in the global table.
// If not found, allocates a new entry, copies the key, and returns a pointer to the value part.
// If found, returns NULL.
Value64* __fastcall GlobalKeyedTable_insert(Key128* key) {
    int count = gKeyedTable.count;
    uint32_t* entries = gKeyedTable.entries;
    uint32_t key1 = key->dwords[0];
    uint32_t key2 = key->dwords[1];
    uint32_t key3 = key->dwords[2];
    uint32_t key4 = key->dwords[3];

    int i = 0;
    if (count > 0) {
        uint32_t* currentEntry = entries;
        do {
            uint32_t entry1 = currentEntry[0];
            uint32_t entry2 = currentEntry[1];
            uint32_t entry3 = currentEntry[2];
            uint32_t entry4 = currentEntry[3];

            // Check exact match of all four 32-bit parts
            if (key1 == entry1 && key2 == entry2 && key3 == entry3 && key4 == entry4) {
                return nullptr; // key already present
            }

            // If key is smaller than current entry (compare as two 64-bit parts), stop iteration.
            // This implies the table is sorted in ascending order of keys.
            // Upper half comparison: key3 and key4 vs entry3 and entry4
            if (key4 < entry4 || (key4 <= entry4 && key3 < entry3)) {
                break;
            }
            // If upper halves equal, compare lower halves
            if (key3 == entry3 && key4 == entry4) {
                if (key2 < entry2 || (key2 <= entry2 && key1 < entry1)) {
                    break;
                }
            }

            i++;
            currentEntry += 6; // each entry is 6 uint32_t
        } while (i < count);
    }

    // Key not found: allocate a new entry and copy key into it
    uint32_t* newEntry = allocateTableEntry();
    if (newEntry == nullptr) {
        return nullptr; // allocation failure, unlikely in game code
    }

    // Copy the 16-byte key
    newEntry[0] = key1;
    newEntry[1] = key2;
    newEntry[2] = key3;
    newEntry[3] = key4;

    // Return pointer to the value part (last 8 bytes of entry)
    return reinterpret_cast<Value64*>(&newEntry[4]);
}