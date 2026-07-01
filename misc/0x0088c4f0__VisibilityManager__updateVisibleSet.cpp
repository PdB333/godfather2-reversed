// FUNC_NAME: VisibilityManager::updateVisibleSet

class VisibilityManager {
public:
    // +0x50: Pointer to array of cell pointers (each cell holds items)
    Cell** m_cells;
    // +0x78: Number of cells
    uint32_t m_cellCount;
    // +0x7c: Pointer to start of output buffer (item entries, size 0x50 each)
    uint8_t* m_outputBufferStart;
    // +0x80: Current write pointer in output buffer
    uint8_t* m_outputBufferCurrent;
    // +0x84: End of output buffer
    uint8_t* m_outputBufferEnd;
    // +0x90: Dynamic array (start pointer) – list of item indices or pointers
    uint32_t* m_listA;
    // +0x94: End of list A
    uint32_t* m_listAEnd;
    // +0x98: ??? (not used here)
    // +0x9c: Start of list B (maybe uint32_t*)
    uint32_t* m_listBStart;
    // +0xa0: Dynamic array B
    uint32_t* m_listB;
    // +0xa4: End of list B
    uint32_t* m_listBEnd;
    // +0x284: A threshold (max distance)
    float m_maxDistSq;
    // +0xae: Flag to prevent re-entrancy
    char m_updateInProgress;

    // Constants from global data
    static const uint32_t kHashTableSize = DAT_00e54200;
    static const uint32_t kHashTableBase = PTR_DAT_00e541fc;

    static constexpr uint32_t kItemSize = 0x50;

    struct ItemEntry {
        // Likely: hash or ID, position, extents, flags, etc.
        uint32_t id;          // +0x00
        uint32_t unknown1;    // +0x04
        uint32_t unknown2;    // +0x08
        uint32_t unknown3;    // +0x0c
        float posX;           // +0x10
        float posY;           // +0x14
        float posZ;           // +0x18
        float radius;         // +0x1c? Actually offset 0x58/0x5c in source?
        // ... many more fields, total 0x50 bytes
    };

    static_assert(sizeof(ItemEntry) == 0x50, "ItemEntry size mismatch");

    // Inner structure for hash map lookup
    struct HashNode {
        uint32_t key;
        uint32_t data;
        HashNode* next; // offset +7? Actually from code: puVar9[7] is next pointer
        // etc.
    };

    void __fastcall updateVisibleSet() {
        if (m_updateInProgress) return;
        m_updateInProgress = 1;

        // 1. Count total items across all cells
        uint32_t totalItems = 0;
        for (uint32_t i = 0; i < m_cellCount; i++) {
            if (m_cells[i]) {
                totalItems += m_cells[i]->itemCount;
            }
        }

        // 2. Build hash table of unique item IDs for deduplication?
        // Actually it builds a mapping from (key0,key1,key2,key3) to an entry.
        // We'll call it "createOrIncrementEntry" pattern.

        for (uint32_t i = 0; i < m_cellCount; i++) {
            Cell* cell = m_cells[i];
            if (!cell || cell->itemCount <= 0) continue;
            for (uint32_t j = 0; j < cell->itemCount; j++) {
                uint32_t* itemData = (uint32_t*)(cell->items + j * 6 * 4); // each item is 6 ulongs? Actually from code: local_a8 += 6 (6 uint32s)
                uint32_t key0 = itemData[0];
                uint32_t key1 = itemData[1];
                uint32_t key2 = itemData[2];
                float key3 = *(float*)&itemData[3];

                // Compute hash: (key0*33 + key1)*33 + key2)*33 + key3
                __int64 hash = __allmul((__int64)(key0 * 33 + key1) * 33 + key2, 33, 0);
                hash = __allmul(hash + (uint32_t)key3, 33, 0);
                uint32_t hash32 = (uint32_t)(hash & 0xFFFFFFFF);

                // Look up in hash table (chained)
                HashNode* node = *(HashNode**)(kHashTableBase + (hash32 % kHashTableSize) * 4);
                HashNode* found = nullptr;
                while (node) {
                    if (node->key == hash32) {
                        found = node;
                        break;
                    }
                    node = node->next; // next at offset +7? Actually puVar9[7] is next pointer
                }
                if (found) {
                    // Increment reference count (stored at found+6)
                    found->refCount++;
                } else {
                    // Insert new node
                    HashNode* newNode = FUN_0088b0c0(&local_80); // local_80 is structure containing key and data
                    newNode->data = itemData;
                    newNode->key = hash32;
                    newNode->refCount = 1;
                    // chain into table
                }
            }
        }

        // 3. Sort the totalItems list by some criterion (call to FUN_0088beb0)
        FUN_0088beb0(totalItems);

        // 4. Second pass: build output buffer (ItemEntry structures) from each cell's item list
        for (uint32_t i = 0; i < m_cellCount; i++) {
            Cell* cell = m_cells[i];
            if (!cell || cell->itemCount <= 0) continue;
            for (uint32_t j = 0; j < cell->itemCount; j++) {
                uint8_t* srcItem = cell->items + j * 0x80; // from local_b4 increment of 0x80
                uint32_t* itemData = (uint32_t*)srcItem;
                uint32_t id = itemData[4]; // offset 0x10
                // Look up item data in hash table
                ItemData* item = FUN_00405720(id, 0);
                if (item) {
                    // Build an ItemEntry
                    ItemEntry entry;
                    entry.someFlag = (item->flags & 1) != 0; // from srcItem[0x50]
                    entry.type = 1;
                    if (srcItem[0x51] & 1) entry.type |= 8;
                    if (srcItem[0x51] & 2) entry.type |= 0x10;
                    entry.posX = *(float*)(srcItem + 0x14);
                    entry.posY = *(float*)(srcItem + 0x18);
                    entry.posZ = *(float*)(srcItem + 0x1c);
                    entry.radiusSq = 0.0f;
                    float r1 = *(float*)(srcItem + 0x58);
                    float r2 = *(float*)(srcItem + 0x5c);
                    if (r1 > 0.0f) entry.radiusSq = r1;
                    else entry.radiusSq = 0.0f;
                    if (r2 > 0.0f) {
                        float maxDist = this->m_maxDistSq;
                        entry.radiusSq = (r2 < maxDist) ? r2 : maxDist;
                    } else {
                        entry.radiusSq = this->m_maxDistSq;
                    }
                    // Copy entry to output buffer
                    if (m_outputBufferCurrent + kItemSize <= m_outputBufferEnd) {
                        memcpy(m_outputBufferCurrent, &entry, kItemSize);
                        m_outputBufferCurrent += kItemSize;
                    } else {
                        FUN_0088a020(m_outputBufferCurrent, &entry);
                    }
                }
            }
        }

        // 5. Process output buffer: split into two lists (opaque/transparent?)
        // After FUN_0088b1a0, we have a list of ItemEntry pointers in buffer
        FUN_0088b1a0(m_outputBufferStart, m_outputBufferCurrent, 0xFFFFFF00); // maybe sort by something

        // 6. Clear temporary lists (called twice)
        FUN_0088c3f0(totalItems);
        FUN_0088c3f0(totalItems);

        // 7. Build two separate lists from buffer entries
        int32_t numEntries = (m_outputBufferCurrent - m_outputBufferStart) / kItemSize;
        for (int32_t idx = 0; idx < numEntries; idx++) {
            uint32_t* entryAddr = (uint32_t*)(m_outputBufferStart + idx * kItemSize);
            // Add to list A
            if (m_listA < m_listAEnd) {
                *m_listA = (uint32_t)entryAddr;
                m_listA++;
            } else {
                FUN_0088b460(m_listA, &entryAddr);
            }
            // Add to list B
            if (m_listB < m_listBEnd) {
                *m_listB = (uint32_t)entryAddr;
                m_listB++;
            } else {
                FUN_0088b460(m_listB, &entryAddr);
            }
        }

        // 8. Final merge/sort? (FUN_0088b230)
        FUN_0088b230(m_listBStart, m_listB, 0xFFFFFF00);
    }
};