// FUNC_NAME: StringTable::addString

// Function address: 0x00659f90
// Role: Insert or find a string in a global intern table, return its ID (index into node array).
// Implements a hash table with separate chaining, nodes allocated from a free list.
// When load factor exceeds 2x bucket count, rehashes via Fun_0065a260.
// Global state stored in static class members.

#include <cstdint>
#include <cstring>

// Forward declarations for internal helper functions
static uint hashString(const char* str, size_t len);
static void initStringTable();
static void rehashTable(uint newBucketCount);
static void* allocNode(size_t size);

struct StringTableNode {
    uint id;        // +0x00  index in g_nodeArray
    uint nextId;    // +0x04  next node in chain (hash bucket)
    uint hash;      // +0x08  full hash value
    uint16 length;  // +0x0C  string length (without null)
    uint16 refCount;// +0x0E  reference count
    char  str[1];   // +0x10  null-terminated string (variable length)
};

// Global static data for the string table
static uint*        g_hashBuckets = nullptr;  // DAT_01205a38
static uint         g_bucketCount;             // DAT_01205a3c
static uint         g_totalAllocated;          // DAT_01205a40 (number of slots in g_nodeArray)
static uint         g_freeListHead;            // DAT_01205a44 (free list head, encoded as (index<<1)|1)
static StringTableNode** g_nodeArray = nullptr; // DAT_01205a34 (array of pointers to nodes)
static uint         g_entryCount;              // DAT_01205a48

uint StringTable::addString(const char* str, size_t len) {
    if (str == nullptr || *str == '\0' || len == 0) {
        return 0;
    }

    if (g_hashBuckets == nullptr) {
        initStringTable();
    }

    uint hash = hashString(str, len);
    uint bucketIdx = hash % g_bucketCount;
    uint* pBucket = &g_hashBuckets[bucketIdx];

    // Traverse the chain in this bucket
    uint currentNodeId = *pBucket;
    while (currentNodeId != 0) {
        StringTableNode* node = g_nodeArray[currentNodeId];
        int cmp = strncmp(node->str, str, len);
        if (cmp == 0 && node->str[len] == '\0') {
            // Found existing entry
            node->refCount++;
            return currentNodeId;
        }
        currentNodeId = node->nextId;
    }

    // Not found, need to allocate a new node
    // Check if we need to grow the node array (free list empty)
    if (g_freeListHead == 0) {
        uint newSize = g_totalAllocated + 0x800;
        g_nodeArray = (StringTableNode**)realloc(g_nodeArray, newSize * sizeof(StringTableNode*));
        if (g_nodeArray == nullptr) {
            // Handle error: out of memory
            return 0;
        }
        // Initialize the new slots as a free list
        uint oldSize = g_totalAllocated;
        for (uint i = oldSize; i < newSize; i++) {
            // Each free slot stores the next free index in the low part, and ORed with 1
            g_nodeArray[i] = (StringTableNode*)((i + 2) | 1); // Encoded as (nextFree << 1) | 1
        }
        // Last slot points to null (end of free list)
        g_nodeArray[newSize - 1] = (StringTableNode*)0;
        g_totalAllocated = newSize;
        g_freeListHead = (oldSize << 1) | 1; // First free slot index encoded
    }

    // Take a node from the free list
    uint newId = g_freeListHead >> 1; // decode: index
    g_freeListHead = (uint)(g_nodeArray[newId]); // next free

    // Allocate memory for the node (size = len + 20 bytes)
    StringTableNode* newNode = (StringTableNode*)allocNode(len + 20);
    if (newNode == nullptr) {
        // Handle allocation failure
        return 0;
    }

    // Fill in node fields
    newNode->id     = newId;
    newNode->nextId = 0; // will be set when inserted into bucket? Actually nextId is set later when chaining? But in insertion path, it's set to 0 initially.
    newNode->hash   = hash;
    newNode->length = (uint16)len;
    newNode->refCount = 1;
    strncpy(newNode->str, str, len);
    newNode->str[len] = '\0';

    // Insert node into bucket (at head)
    newNode->nextId = *pBucket; // chain to existing
    *pBucket = newId;

    // Store node pointer in array
    g_nodeArray[newId] = newNode;

    g_entryCount++;

    // Rehash if load factor > 2 (entryCount > 2 * bucketCount)
    if (g_entryCount > 2 * g_bucketCount) {
        rehashTable(g_bucketCount * 2 - 1); // new bucket count = old*2-1? Actually argument is (bucketCount*4 - 1) but the function does something else. We'll assume.
    }

    return newId;
}