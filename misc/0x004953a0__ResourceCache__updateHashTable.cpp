// FUNC_NAME: ResourceCache::updateHashTable
class ResourceCache {
public:
    // Member offsets (assumed relative to this)
    // +0x210: uint32_t m_numTables
    // +0x214: BucketEntry m_buckets[]   (each entry: uint32_t count, padding to 20? but pointer arithmetic uses puVar5[4] - see code)
    // Global tables (actually member arrays)
    // +???    HashSlot** m_tableBases     (indexed by loop index, accessed via DAT_01217b10)
    // +???    uint32_t* m_tableSizes      (accessed via DAT_01217b00)
    // Global flags:
    static volatile int32_t g_updateInProgress;   // DAT_01217d34
    static volatile int32_t g_pendingFree;        // DAT_01217d38

    struct HashSlot {
        uint8_t  data[0x14];               // unknown, offset 0x00-0x13
        uint32_t keyLow;                   // +0x14
        uint32_t keyHigh;                  // +0x18
        // total size 0x1c
    };

    struct BucketEntry {
        uint32_t numSlots;                 // *puVar5
        uint8_t  _pad[0x14];              // padding? based on puVar5[4] being at offset 16
        HashSlot* slotArray;              // puVar5[4] at offset 16 from start of entry
        // each BucketEntry size assumed 20 bytes but pointer arithmetic uses increment by 4? 
        // More likely the decompiler miscast; we'll treat the array and slotArray as separate members.
    };

    void updateHashTable() {
        if (m_numTables == 0)
            return;

        BucketEntry* currentBucket = reinterpret_cast<BucketEntry*>(reinterpret_cast<uint8_t*>(this) + 0x214);

        for (uint32_t tableIdx = 0; tableIdx < m_numTables; ++tableIdx, ++currentBucket) {
            if (currentBucket->numSlots == 0)
                continue;

            HashSlot* slots = currentBucket->slotArray;
            for (uint32_t slotIdx = 0; slotIdx < currentBucket->numSlots; ++slotIdx) {
                uint32_t uVar2 = slots[slotIdx].keyLow;  // actually read from puVar5[4] + ... but we simplify

                // The original code computed index into a separate hash table using global arrays:
                // base = m_tableBases[tableIdx] (interpreted from global const difference)
                // size = m_tableSizes[tableIdx]
                // slotPtr = base + (uVar2 % size) * sizeof(HashSlot)
                uint32_t hashIdx = uVar2 % m_tableSizes[tableIdx];
                HashSlot* slotPtr = &m_tableBases[tableIdx][hashIdx];

                if (uVar2 != slotPtr->keyHigh && uVar2 == slotPtr->keyLow) {
                    // Potential collision detected: same low key, different high key
                    if (g_updateInProgress != 0) {
                        lock();
                        int32_t oldFree = g_pendingFree;
                        g_pendingFree = 0;
                        unlock();
                        if (oldFree != 0) {
                            freeResource(oldFree);   // FUN_00ab51e0 likely
                        }
                    }
                    resolveCollision(slotPtr);       // FUN_00495490
                }
            }
        }
    }

private:
    // Inline lock/unlock (platform specific)
    void lock() { /* ... */ }
    void unlock() { /* ... */ }

    void freeResource(int32_t param) { /* ... */ }
    void resolveCollision(HashSlot* slot) { /* ... */ }
};

// Static globals (from code)
volatile int32_t ResourceCache::g_updateInProgress;
volatile int32_t ResourceCache::g_pendingFree;