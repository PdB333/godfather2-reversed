// FUNC_NAME: HashTable::initialize
// Logic for initializing the hash table: allocates the structure, bucket array, and node pool, then inserts initial entries.

#include <cstdint>

// Forward declarations for functions used
extern "C" {
    void* __cdecl operator new(size_t size); // or custom allocator
    void* __cdecl malloc(size_t size);
    bool getNextKey(uint*& keyPtr); // function at 0x006f5e20, returns false when no more keys
    void rehashTable(); // function at 0x006f56c0
}

// Hash node structure (20 bytes each in the node pool)
struct HashNode {
    uint32_t hash;        // +0x00: cached hash of key (or key itself)
    uint32_t key;         // +0x04: the key value
    uint32_t value;       // +0x08: associated value
    union {
        uint32_t pad;     // +0x0C: padding
        HashNode* next;   // used for free list linking
    };
};

// Hash table structure (24 bytes = 6 ints)
struct HashTable {
    HashNode** buckets;   // +0x00: pointer to array of bucket heads
    uint32_t tableSize;   // +0x04: number of buckets
    HashNode* freeList;   // +0x08: head of free node list
    uint32_t elementCount;// +0x0C: number of elements currently in table
    HashNode* nodePool;   // +0x10: pointer to pre-allocated node pool (linked list)
    uint8_t flags;        // +0x14: flags (e.g., 0x01 = rehash allowed)
};

// Global hash table instance
static HashTable* g_table = nullptr;  // originally DAT_0112aa04
static int32_t g_initialized = 0;     // originally DAT_0112aa08

// Function entry point
void __thiscall HashTable::initialize(void) {
    // Save a debug canary value (unused in this function)
    uint32_t canary = DAT_01129974; // likely a global debug constant

    // Mark as initializing
    g_initialized = 0;

    // Step 1: Allocate the hash table structure (24 bytes)
    HashTable* newTable = (HashTable*)::operator new(sizeof(HashTable));
    if (newTable == nullptr) {
        g_table = nullptr;
        return;
    }

    // Step 2: Allocate the bucket array (64 bytes = 16 buckets of 4-byte pointers)
    HashNode** buckets = (HashNode**)::operator new(64); // 0x40 bytes
    newTable->buckets = buckets;
    newTable->tableSize = 16; // default bucket count

    // Step 3: Initialize node pool (256 nodes, each 20 bytes, total 0x1004?)
    // The pool allocation size is 0x1004 bytes. We'll replicate the logic exactly.
    HashNode* pool = (HashNode*)::malloc(0x1004);
    if (pool != nullptr) {
        // Initialize the pool as a linked list of free nodes.
        // Each node is 20 bytes (5 int32_t/dwords). We'll trust the decompiled loop.
        HashNode* cur = pool;
        int count = 0xFF; // 255 iterations
        do {
            // Set the next pointer of current node to point 5 dwords ahead (20 bytes)
            cur->next = (HashNode*)((uint32_t)cur + 20);
            count--;
            cur = (HashNode*)((uint32_t)cur + 16); // move by 4 ints = 16 bytes (???)
        } while (count != 0);
        // Set last node's next to 0
        ((uint32_t*)pool)[0x400] = 0; // at offset 0x1000? Not precise.
        // Attach the pool to the table's free list chain
        pool->next = newTable->freeList; // newTable->freeList is actually field +0x08? Wait, field order: freeList is +0x08.
        // Actually the decompiled code does: *piVar6 = piVar3[4]; where piVar3[4] is field +0x10 (nodePool). So we link the new pool to the existing nodePool chain.
        newTable->nodePool = pool; // plus other linking? The code sets the first node's next to the old nodePool.
        // Then it sets the free list head to pool+1 (second node)
        newTable->freeList = (HashNode*)((uint32_t)pool + sizeof(HashNode)); // piVar6+1
    } else {
        newTable->freeList = nullptr;
    }

    // Step 4: Insert initial keys from a source (callback)
    uint* keyPtr = nullptr;
    HashTable* tbl = g_table; // originally piVar3
    while (getNextKey(&keyPtr) != '\0') {
        uint32_t key = *keyPtr;
        uint32_t bucketIndex = key % tbl->tableSize;

        // Check if rehash needed (if more than 2x capacity and rehash flag set)
        if ((tbl->flags != 0) && (tbl->elementCount >= tbl->tableSize * 2)) {
            rehashTable();
            bucketIndex = key % tbl->tableSize; // recompute after rehash
        }

        // Get a free node from the pool
        HashNode* node = tbl->freeList;
        if (node == nullptr) {
            // No free node; allocate a new block of nodes (like the pool initialization)
            // This replicates the a block allocation and linking logic.
            HashNode* newBlock = (HashNode*)::operator new(0x1004); // or malloc
            if (newBlock) {
                // Initialize internal linked list
                HashNode* cur = newBlock;
                int i = 0xFF;
                do {
                    cur->next = (HashNode*)((uint32_t)cur + 20);
                    i--;
                    cur = (HashNode*)((uint32_t)cur + 16);
                } while (i != 0);
                // Set last node's next to 0 (the sentinel)
                ((uint32_t*)newBlock)[0x400] = 0;
                // Link the new block into the table's chain
                newBlock->next = tbl->nodePool;
                tbl->nodePool = newBlock;
                // Set free list head to second node
                tbl->freeList = (HashNode*)((uint32_t)newBlock + sizeof(HashNode));
                node = tbl->freeList;
            }
        }

        // Remove node from free list
        tbl->freeList = node->next;  // actually piVar3[2] = puVar7[3] (node->next)
        node->next = nullptr;       // puVar7[3] = 0
        tbl->elementCount++;        // piVar3[3]++

        // Fill node data
        node->key = key;            // puVar7[1] = key
        node->value = 0;            // puVar7[2] = 0
        node->hash = key;           // *puVar7 = key (also stored as hash)

        // Insert into bucket
        node->next = tbl->buckets[bucketIndex]; // puVar7[3] = *(uint*)(*piVar3 + bucketIndex*4)
        tbl->buckets[bucketIndex] = node;       // *(uint**)(*piVar3 + bucketIndex*4) = node
    }

    // Finalize global pointer
    g_table = tbl;
    return;
}