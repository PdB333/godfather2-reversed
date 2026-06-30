// FUNC_NAME: AptNativeHash::lookup
// Address: 0x005BB050
// Source: AptNativeHash.cpp line ~299
// EA Apt hash map lookup: finds value by case-insensitive string key.
// Hash table layout: [0] log2 bucket count (1 byte), [2] entry count (short), [4] bucket array pointer.
// Node layout: [0] ptr to key-value struct (key string at +0xC), [4] value (int), [8] next node, [12] hash.

#include <cstring>

class AptNativeHash {
public:
    int lookup(const char* key) const;
};

int AptNativeHash::lookup(const char* key) const {
    // Debug assertion: key must not be null (source AptNativeHash.cpp:299)
    if (key == nullptr) {
        // In original EA debug build, this triggers __debugbreak and assertion logging
        return 0;
    }

    // Short count at +2 indicates if table is non-empty
    if (*(short*)((const char*)this + 2) == 0) {
        return 0;
    }

    uint32_t hash = /* FUN_005b87d0 */ hashString(key);  // hash function for strings

    // Bucket mask: (1 << (*this & 0x1F)) - 1
    uint32_t mask = (1 << (*(const uint8_t*)this & 0x1F)) - 1;
    uint32_t bucketIndex = hash & mask;

    // Bucket array at offset +4
    int* bucket = *(int**)((const char*)this + 4);
    int* node = (int*)bucket[bucketIndex];

    while (node != nullptr) {
        // node[3] is stored hash, node[1] is value, node[2] is next pointer
        // node[0] points to a key-value struct; key string at node[0]+0xC
        if ((uint32_t)node[3] == hash &&
            _stricmp(*(const char**)(node[0] + 0xC), key) == 0) {
            return node[1];  // found -> return associated integer value
        }
        node = (int*)node[2];
    }

    return 0;  // not found
}