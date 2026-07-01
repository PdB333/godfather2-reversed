// FUNC_NAME: AptNativeHash::set
// Reconstructed from Ghidra at address 0x005baa90
// EA AptNativeHash (AptNativeHash.cpp) - Insert or update a key-value pair in a hash table.
// If value is 0, the key is removed (delegates to removeEntry).
// Debug assertions (from file "..\\source\\Apt\\AptNativeHash.cpp") are simplified with assert().

class AptNativeHash; // forward

// Helper structures (simplified)
struct AptString; // 0x24 byte string object

// External function declarations (EA engine)
extern "C" uint32 __fastcall hashString(const char* key);           // 0x005b87d0
extern "C" void __fastcall removeEntry(AptNativeHash* hash, const char* key); // 0x005baee0
extern "C" void __fastcall lockHashMutex();                         // 0x0059c690
extern "C" void __fastcall unlockHashMutex();                       // 0x0059c690 (used as unlock after?)
extern "C" AptString* __fastcall createString(const char* src);    // 0x005a0a80 + 0x005b8920 combined

class AptNativeHash {
public:
    // Hash table structure (offset 0x00, 0x02, 0x04)
    uint8_t  m_bucketLog2;    // +0x00: log2 of number of buckets
    uint16_t m_entryCount;    // +0x02: number of stored entries
    Entry**  m_buckets;       // +0x04: array of bucket head pointers (size 1 << m_bucketLog2)

    // Entry structure (size 0x10)
    struct Entry {
        AptString* pKey;     // +0x00
        int32_t    pValue;   // +0x04 (value parameter)
        Entry*     pNext;    // +0x08
        uint32_t   hash;     // +0x0C (precomputed hash for the key)
    };

    // Main function: set or remove a key-value pair
    void __thiscall set(const char* key, int32_t value) {
        if (key == nullptr) {
            assert("pKey" && false); // Debug assert
        }

        // If value is 0, remove the key
        if (value == 0) {
            removeEntry(this, key);
            return;
        }

        // Compute hash from key
        uint32_t hash = hashString(key);
        // Number of buckets = 1 << (m_bucketLog2 & 0x1f)
        uint32_t bucketIndex = ((1 << (m_bucketLog2 & 0x1f)) - 1) & hash;

        // Search existing entries in the bucket
        if (m_entryCount > 0) {
            for (Entry* pEntry = m_buckets[bucketIndex]; pEntry != nullptr; pEntry = pEntry->pNext) {
                assert(pEntry->pKey != nullptr); // Debug assert
                // Check hash match first, then string compare
                if (pEntry->hash == hash && _stricmp(pEntry->pKey->getString(), key) == 0) {
                    // Key found: update the value
                    assert(pEntry->pValue != 0); // Debug assert (pEntry->pValue should not be null)
                    if (pEntry->pValue != value) {
                        lockHashMutex();
                        // Possibly release old value? Not shown in decompiled, but here we just assign
                        pEntry->pValue = value;
                        unlockHashMutex();
                    }
                    return;
                }
            }
        }

        // Key not found: create a new entry and insert at head of bucket
        Entry* newEntry = (Entry*)malloc(0x10);
        assert(newEntry != nullptr); // Could not allocate entry

        newEntry->hash = hash;

        // Create a new AptString for the key
        AptString* keyString = (AptString*)malloc(0x24);
        if (keyString != nullptr) {
            // Initialize string object (simplified)
            keyString->flags = (keyString->flags & 0xFFFF8001) | 1;
            keyString->length = 0;
            keyString->flags |= 0x8000;
            keyString->init(key);          // FUN_005a0a80 (assign string data)
            keyString->magic = 0xbeefceec; // Debug magic
        }

        // Copy key string into newEntry
        lockHashMutex();
        newEntry->pKey = keyString;
        unlockHashMutex();
        newEntry->pValue = value;
        newEntry->pNext = static_cast<Entry*>(m_buckets[bucketIndex]);
        m_buckets[bucketIndex] = newEntry;
        m_entryCount++;
    }
};

// Note: The original code uses a global hash function (hashString) that relies on the
// first character of the key to compute the bucket mask. The bucket count is derived from
// the first byte of the hash table structure (m_bucketLog2). The entry's key is stored as
// an AptString object allocated separately. Mutex operations (lock/unlock) are used around
// critical sections. Debug assertions reference file "..\\source\\Apt\\AptNativeHash.cpp".