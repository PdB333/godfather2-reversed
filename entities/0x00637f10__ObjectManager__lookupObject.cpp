// FUNC_NAME: ObjectManager::lookupObject
// Function at 0x00637f10: Lookup an object by ID, using direct array for small IDs and a hash table otherwise.
// The class structure (this in ESI):
// +0x07: uint8_t hashShift; // used to compute hash table size: (1 << (hashShift & 0x1f)) - 1 | 1
// +0x0C: int* directArray; // base pointer to array of 8-byte entries indexed by ID - 1
// +0x10: HashNode** hashTable; // array of bucket pointers, each bucket 0x14 bytes
// +0x1C: int32_t maxDirectID; // if ID is >0 and <= this, use direct array
// DAT_00e2b1a4 is a global constant (assumed int) used in hash computation.
// DAT_00e2a93c is a global sentinel value representing "not found".

#include <cstdint>

// Node structure for hash table chaining (size 0x14 = 20 bytes)
struct HashNode {
    int32_t type;     // +0x00: type identifier (must be 3 for valid entry)
    int32_t key;      // +0x04: the ID
    int32_t data[2];  // +0x08: data payload (size varies, but at least 2 ints)
    HashNode* next;   // +0x10: next node in bucket chain
};

class ObjectManager {
public:
    // Look up by ID. Returns pointer to data portion of entry, or &invalidSentinel if not found.
    int* lookupObject(int id) {
        if ((id > 0) && (id <= this->maxDirectID)) {
            // Direct access: array of 8-byte entries starting at index 1.
            // directArray points to the first element (id=1), so entry at id is at directArray + (id-1)*8.
            return reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this->directArray) - 8 + id * 8);
        }

        // Hash table lookup
        uint32_t hashMask = (1 << (this->hashShift & 0x1f)) - 1;
        // Ensure mask is odd (at least 1)
        hashMask = (hashMask | 1);
        uint32_t bucketIndex = (static_cast<uint32_t>(static_cast<float>(id) + HASH_OFFSET_FLOAT)) % hashMask;
        // HASH_OFFSET_FLOAT is a global constant (DAT_00e2b1a4) used as float

        HashNode* node = this->hashTable[bucketIndex];
        while (node != nullptr) {
            if ((node->type == 3) && (node->key == id)) {
                // Return pointer to data (skip type and key)
                return &node->data[0];
            }
            node = node->next;
        }

        // Not found – return sentinel
        return &invalidSentinel;
    }

private:
    uint8_t hashShift;          // +0x07
    uint8_t padding[4];         // alignment (offset 0x08-0x0B)
    int* directArray;           // +0x0C
    HashNode** hashTable;       // +0x10
    int32_t maxDirectID;        // +0x1C

    static int invalidSentinel;  // DAT_00e2a93c
    static constexpr float HASH_OFFSET_FLOAT = reinterpret_cast<float&>(0x00e2b1a4); // actual value unknown
};

// Global sentinel value (must be defined elsewhere)
int ObjectManager::invalidSentinel = 0; // placeholder