// FUNC_NAME: HashTable::findEntry

// Function address: 0x0056e290
// Role: Hash table lookup with multiple key comparison (int ID, float coord, int type, int subtype).
// Uses a bucket array at this+0x30, linked list nodes with next pointer at +0x30.
// Provides count metrics for profiling.

#include <cstdint>

// Global constants used by the function (from data refs)
static const uint32_t SIGN_MASK = 0x7FFFFFFF;  // DAT_00e44680
static const float EPSILON = 0.0f;             // DAT_00e2e780 (actual value unknown, likely small)

// Key structure passed as param_2
struct SearchKey {
    int32_t id;            // [0] - primary ID
    int32_t bucketIndex;   // [1] - index into bucket array
    float coord;           // [2] - float key (e.g., position, timestamp)
    int32_t type;          // [3] - secondary key
    int32_t subtype;       // [4] - tertiary key
};

// Node structure for hash table chains
struct HashNode {
    // Offsets (relative to node base):
    // +0x00: unknown (maybe vtable/refCount)
    // +0x08: int id
    // +0x10: float coord
    // +0x14: int type
    // +0x18: int subtype
    // +0x30: next pointer
    // Total size at least 0x34 bytes
    uint8_t unknown_00[8];   // +0x00
    int32_t id;              // +0x08
    float coord;             // +0x10
    int32_t type;            // +0x14
    int32_t subtype;         // +0x18
    uint8_t unknown_1C[0x14]; // +0x1C to +0x30 (padding or other fields)
    HashNode* next;          // +0x30
};

class HashTable {
public:
    // Member offsets (relative to this):
    // +0x1030? Actually bucket array starts at +0x30, counters at +0x1034+
    // Bucket array: HashNode* buckets[]; located at this+0x30 (each entry is 4 bytes)
    // The array length is unknown but inferred from bucketIndex usage.

    HashNode* findEntry(const SearchKey& key) {
        // Increment total call counter
        *(reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x1034)) += 1;

        uint32_t mask = SIGN_MASK;  // 0x7FFFFFFF
        float epsilon = EPSILON;    // global tolerance

        // Get the head of the linked list for the given bucket
        HashNode* node = *(reinterpret_cast<HashNode**>(
            reinterpret_cast<uint8_t*>(this) + 0x30 + key.bucketIndex * 4));

        while (true) {
            if (node == nullptr) {
                // Empty bucket - increment miss counter
                *(reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x103C)) += 1;
                return nullptr;
            }

            // Compare the search key against the current node
            bool idMatch = (key.id == node->id);
            // Floating-point absolute difference with sign masking
            float diff = key.coord - node->coord;
            uint32_t absDiffBits = (*reinterpret_cast<uint32_t*>(&diff)) & mask;
            float absDiff = *reinterpret_cast<float*>(&absDiffBits);
            bool coordMatch = (absDiff < epsilon);
            bool typeMatch = (key.type == node->type);
            bool subtypeMatch = (key.subtype == node->subtype);

            if (idMatch && coordMatch && typeMatch && subtypeMatch) {
                // Found matching node - increment hit counter
                *(reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x1038)) += 1;
                return node;
            }

            // Did not match - increment probe counter (number of nodes examined)
            *(reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(this) + 0x1040)) += 1;
            node = node->next;
        }
    }
};