// FUNC_NAME: StringHashTable::findOrCreateEntry

#include <cstdint>

// Hash table entry structure: first uint is hash, second uint is pointer to next
struct HashEntry {
    uint32_t hash;
    HashEntry* next;
};

// Global pointer to the bucket array (256 entries)
extern HashEntry** gHashTableBase;  // Address: 0x01205960

// Forward declaration of allocation function (address: 0x006162e0)
HashEntry* allocateHashEntry(uint32_t hash, HashEntry*& bucketHead);

// Look up or create a hash table entry for a null-terminated string.
// Returns pointer to the entry (its first uint is the hash).
// Uses ELF hash: each byte multiplied by 0x1003f (i.e., shift left 8, add some)
HashEntry* StringHashTable::findOrCreateEntry(const char* str) {
    if (str == nullptr) {
        return nullptr;
    }

    // Compute ELF-style hash
    uint32_t hash = 0;
    while (*str != '\0') {
        hash = hash * 0x1003f + static_cast<uint8_t>(*str);
        ++str;
    }

    // Bucket index = hash mod 256 (table size 256)
    uint32_t bucketIndex = hash & 0xFF;
    HashEntry* entry = gHashTableBase[bucketIndex];

    // Scan chain for matching hash
    while (entry != nullptr) {
        if (entry->hash == hash) {
            return entry;
        }
        entry = entry->next;
    }

    // Not found – create a new entry (allocation function handles insertion into bucket)
    return allocateHashEntry(hash, gHashTableBase[bucketIndex]);
}