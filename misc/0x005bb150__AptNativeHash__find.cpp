// FUNC_NAME: AptNativeHash::find
// Function address: 0x005bb150
// Role: Lookup a key object in a hash table and return the associated integer value.
// The hash table is part of the Apt UI system (Adobe Flash integration).
// Key objects are compared by pointer identity, then by hash, then by ID (offset 4) and name string (offset 12).

// Node structure for the hash table's linked list buckets.
struct AptHashNode {
    void* key;          // +0x00 pointer to the key object
    int value;          // +0x04 mapped integer value
    AptHashNode* next;  // +0x08 next node in bucket chain
    uint hash;          // +0x0C full hash value of the key (for early rejection)
};

// Hash table class (from AptNativeHash.cpp)
class AptNativeHash {
public:
    uint8 m_exponent;   // +0x00 number of bits for bucket count (buckets = 1 << exponent)
    short m_count;      // +0x02 number of elements stored (if zero, skip search)
    AptHashNode** m_buckets; // +0x04 pointer to array of bucket heads (size = 1<<exponent)

    // External hash function (likely uses key's name string)
    static uint hashKey(void* key);
};

// The actual lookup function. In the original code, the key object is passed in EAX (register)
// but for clarity we model it as a normal parameter.
int AptNativeHash::find(void* key) {
    // Debug assertion: if key is null, trigger breakpoint.
    if (key == nullptr) {
        // File: ..\source\Apt\AptNativeHash.cpp, line 0x144 (324)
        // Assertion failed: key != 0
        // In debug builds this would trigger a debug break.
        // Remove in release.
        __debugbreak();
        return 0;
    }

    // If the hash table is empty, return immediately.
    if (m_count == 0) {
        return 0;
    }

    // Compute the hash of the key using the external hash function.
    uint hash = hashKey(key);

    // Calculate bucket index: hash & (numBuckets-1), where numBuckets = 1 << exponent.
    uint numBuckets = 1 << (m_exponent & 0x1F); // ensure shift is valid
    uint bucketIndex = hash & (numBuckets - 1);

    // Walk the chain in the selected bucket.
    for (AptHashNode* node = m_buckets[bucketIndex]; node != nullptr; node = node->next) {
        void* currentKey = node->key;

        // Quick check 1: pointer equality (same object).
        if (currentKey == key) {
            return node->value;
        }

        // Quick check 2: compare full hashes.
        if (node->hash != hash) {
            continue;
        }

        // Compare key content: at offset 4 (int ID), and offset 12 (string name).
        // The key object is assumed to have these fields.
        int id1 = *(int*)((char*)currentKey + 4);
        int id2 = *(int*)((char*)key + 4);
        if (id1 != id2) {
            continue;
        }

        const char* name1 = *(const char**)((char*)currentKey + 12);
        const char* name2 = *(const char**)((char*)key + 12);
        if (__stricmp(name1, name2) == 0) {
            return node->value;
        }
    }

    // Not found.
    return 0;
}