// FUNC_NAME: EntityReplicationManager::processReplicationUpdate
static uint hashTableKey;
static uint hashTableCount;
// Global hash table structures (DAT_0112a99c, DAT_0112a9a0)
struct HashNode {
    uint32_t key;          // +0x00
    uint16_t flags;        // +0x04
    uint16_t unk6;         // +0x06
    HashNode* prev;        // +0x08
    HashNode* next;        // +0x0C
    HashNode* hashNext;    // +0x10
};

struct ReplicationEntry {
    uint32_t id;           // +0x00 (key)
    uint32_t hash;         // +0x04 (hash for the hash table)
    uint32_t count;        // +0x08 (number of sub-elements)
    // +0x0C: some data array
};

struct ReplicationContext {
    int32_t mode;          // +0x00
    int32_t unk4;          // +0x04
    int32_t entryCount;    // +0x08
    ReplicationEntry entries[]; // +0x0C
};

// Global hash table for replication IDs
HashTable* g_replicationHashTable = (HashTable*)0x0112a99c; // DAT_0112a99c
// Global hash table for sub-element IDs
HashTable* g_subElementHashTable = (HashTable*)0x0112a9a0; // DAT_0112a9a0

extern "C" {
    void* memAlloc(uint32_t size); // FUN_009c8e50
    bool hashInsert(HashNode* node, uint32_t key); // FUN_00408260
    bool addToPendingList(void* base, HashNode* node, uint32_t flags); // FUN_00408900
    void rehashReplicationTable(); // FUN_006e60e0
    uint32_t hashData16(const uint32_t data[4], uint32_t len); // FUN_004db320
    void rehashSubElementTable(); // FUN_006e6f20
    HashNode* allocateHashNode(); // FUN_006e73f0
    void initHashNode(HashNode* node); // FUN_006e7260
    uint32_t getReplicationKey(ReplicationEntry* entry); // FUN_004213e0
    ReplicationContext* getReplicationContext(); // FUN_0049c9c0
}

int* __fastcall processReplicationUpdate(ReplicationEntry* entry) {
    uint32_t key;
    ReplicationContext* ctx = getReplicationContext();
    HashNode* node;
    uint32_t hashValue;
    uint32_t index;
    HashNode** bucket;
    HashNode* existingNode;
    HashNode* newNode;
    uint32_t subHash;
    uint32_t subIndex;
    HashNode** subBucket;
    void* subNode;
    uint32_t data[4];
    uint32_t subData[4];

    // Get the replication key from the entry
    HashNode* keyNode = (HashNode*)getReplicationKey(&key);
    key = *keyNode;

    if (ctx->mode != 2) {
        return (int*)ctx;
    }

    ReplicationEntry* currentEntry = &ctx->entries[0];
    for (int i = 0; i < ctx->entryCount; i++, currentEntry++) {
        currentEntry->id = key; // set the ID for this entry

        if (currentEntry->hash != 0) {
            // Look for existing node in hash table by hash value
            uint32_t bucketIndex = currentEntry->hash % g_replicationHashTable->size;
            bucket = &g_replicationHashTable->buckets[bucketIndex];
            existingNode = *bucket;
            while (existingNode != nullptr && existingNode->key != currentEntry->hash) {
                existingNode = existingNode->hashNext;
            }

            if (existingNode == nullptr) {
                // Allocate new hash node
                newNode = (HashNode*)memAlloc(20);
                if (newNode != nullptr) {
                    newNode->key = 0;
                    newNode->flags = 0;
                    newNode->unk6 = 0;
                    newNode->prev = nullptr;
                    newNode->next = nullptr;
                    newNode->hashNext = nullptr;

                    hashInsert(newNode, currentEntry->hash);
                    if (newNode->key != 0) {
                        addToPendingList((void*)((int)entry - 12), newNode, 0x8000);
                    }

                    // Rehash if load factor is too high
                    if (g_replicationHashTable->loadFactorThreshold != 0 &&
                        (uint32_t)(g_replicationHashTable->size * 2) <= g_replicationHashTable->numEntries) {
                        rehashReplicationTable();
                        bucketIndex = newNode->key % g_replicationHashTable->size;
                    }

                    // Insert into hash table bucket
                    newNode->hashNext = *bucket;
                    *bucket = newNode;
                    g_replicationHashTable->numEntries++;
                } else {
                    newNode = nullptr;
                }

                // Insert into linked list (doubly linked)
                *((uint32_t*)currentEntry) = newNode->prev; // Actually this sets currentEntry->prev? Wait: code does *puVar3 = puVar5[2]; puVar3[1] = 0; then if puVar5[2]==0 set puVar5[3]=puVar3 else set puVar5[2]+4 = puVar3. This is a bit reversed, likely setting currentEntry as part of node list.
                // Simplified: we'll maintain the list as per original code
                newNode->prev = (HashNode*)currentEntry;
                newNode->next = nullptr;
                if (newNode->prev != nullptr) {
                    newNode->prev->next = newNode;
                }
                newNode->next = (HashNode*)currentEntry;
            }
        }

        // Process sub-elements (inner loop)
        uint32_t subCount = currentEntry->count;
        HashNode* subNodePtr = (HashNode*)(currentEntry + 7); // +0x1C? Actually offset by 7 uint32s? But original uses pointer arithmetic: puVar5 = puVar3 + 7; then later puVar8 = puVar3 + 0xc; So each sub-element is 0x23 uint32s apart (0x8C bytes). This is complex, simplified version below.
        // We'll just show the overall pattern.

        for (uint32_t j = 0; j < subCount; j++) {
            // Initialize sub-node
            if (subNodePtr != nullptr) {
                // Clear fields
                *((uint32_t*)subNodePtr) = 0;
                *((uint32_t*)subNodePtr + 1) = 0;
                *((uint32_t*)subNodePtr + 2) = 0;
                subNodePtr->flags = (uint16_t)&PTR_FUN_00d5faf8; // vtable?
                *((uint32_t*)subNodePtr + 0x13) = 0;
                *((uint32_t*)subNodePtr + 0x14) = 0;
                *(uint8_t*)((int)subNodePtr + 0x77) = 0;
            }

            // Compute hash from 16-byte data
            data[0] = *((uint32_t*)subNodePtr - 4); // -4 uint? Actually from code: local_20 = puVar8[-1]; local_1c = *puVar8; etc.
            data[1] = *((uint32_t*)subNodePtr - 3);
            data[2] = *((uint32_t*)subNodePtr - 2);
            data[3] = *((uint32_t*)subNodePtr - 1);
            hashData16(data, 16); // dummy, it's used for hash calculation
            subHash = hashData16(&data, 16) % g_subElementHashTable->size;

            // Rehash if needed
            if (g_subElementHashTable->loadFactorThreshold &&
                (uint32_t)(g_subElementHashTable->size * 2) <= g_subElementHashTable->numEntries) {
                rehashSubElementTable();
                subData[0] = *((uint32_t*)subNodePtr - 4);
                subData[1] = *((uint32_t*)subNodePtr - 3);
                subData[2] = *((uint32_t*)subNodePtr - 2);
                subData[3] = *((uint32_t*)subNodePtr - 1);
                hashData16(subData, 16);
                subHash = hashData16(&subData, 16) % g_subElementHashTable->size;
            }

            // Allocate from free list or create
            HashNode* freeNode = g_subElementHashTable->freeList;
            if (freeNode == nullptr) {
                // Try to get from another pool
                freeNode = (HashNode*)allocateHashNode();
            }
            // Insert into hash table
            g_subElementHashTable->freeList = (HashNode*)freeNode->hashNext; // unlink
            freeNode->hashNext = nullptr;
            g_subElementHashTable->numEntries++;

            *((uint32_t*)freeNode) = (uint32_t)subNodePtr; // store pointer to subNode
            uint32_t bucketIndex = subHash;
            freeNode->hashNext = g_subElementHashTable->buckets[bucketIndex];
            g_subElementHashTable->buckets[bucketIndex] = freeNode;

            // Initialize subNode
            initHashNode(subNodePtr);

            // Advance to next sub-element
            subNodePtr = (HashNode*)((uint32_t*)subNodePtr + 0x23);
        }
    }

    return (int*)ctx;
}