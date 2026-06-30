// FUNC_NAME: GhostManager::registerGhostObject
#include <cstdint>

// Forward declarations
struct GhostListItem;
struct GhostHashNode;
struct GhostHashTable;

// Global variables (from Ghidra)
extern uint8_t* gGameContext; // DAT_0122337c
extern GhostHashTable* gGhostHashTable; // DAT_012053b0

// Memory allocator (from Ghidra)
extern void* FUN_009c8e50(uint32_t size);
extern void FUN_00421cb0(GhostHashTable* table); // resize hash table

// Structure definitions based on offsets
struct GhostListItem {
    void* object;     // +0x00: pointer to the registered object (e.g., Ghost*)
    GhostListItem* next; // +0x04
};

struct GhostHashNode {
    uint32_t key;           // +0x00: ghost ID or context-dependent key
    GhostListItem* listHead; // +0x04: linked list of registered objects
    int32_t count;          // +0x08: number of items in list
    uint32_t eventMask;     // +0x0C: bitmask of event types handled
    GhostHashNode* next;    // +0x10: next node in hash bucket chain
};

struct GhostHashTable {
    GhostHashNode** buckets;    // +0x00: pointer to bucket array
    uint32_t bucketCount;       // +0x04: number of buckets
    uint32_t itemCount;         // +0x08: total number of hash nodes
    char resizeEnabled;         // +0x0C: flag to allow automatic resize
    // padding to 4 bytes
};

void GhostManager::registerGhostObject(void* param_1)
{
    // Get key from game context (e.g., current actor ID or network session)
    uint32_t key = 0;
    if (*(int32_t*)(gGameContext + 0x84) != 0) {
        key = *(uint32_t*)(*(int32_t*)(gGameContext + 0x84) + 0x1C);
    }

    // Look up hash node for this key
    uint32_t bucketIndex = key % gGhostHashTable->bucketCount;
    GhostHashNode* node = gGhostHashTable->buckets[bucketIndex];
    while (node != nullptr && node->key != key) {
        node = node->next;
    }

    // If no node exists, create one
    if (node == nullptr) {
        node = (GhostHashNode*)FUN_009c8e50(sizeof(GhostHashNode)); // 0x14
        if (node != nullptr) {
            node->key = key;
            node->listHead = nullptr;
            node->count = 0;
            node->eventMask = 0;
            node->next = nullptr;
        }

        // Insert into hash table (may trigger resize)
        bucketIndex = node->key % gGhostHashTable->bucketCount;
        if (gGhostHashTable->resizeEnabled && 
            (gGhostHashTable->itemCount >= 2 * gGhostHashTable->bucketCount)) {
            FUN_00421cb0(gGhostHashTable);
            bucketIndex = node->key % gGhostHashTable->bucketCount;
        }
        node->next = gGhostHashTable->buckets[bucketIndex];
        gGhostHashTable->buckets[bucketIndex] = node;
        gGhostHashTable->itemCount++;
    }

    // Allocate list item for the new object
    GhostListItem* item = (GhostListItem*)FUN_009c8e50(sizeof(GhostListItem)); // 8
    if (item != nullptr) {
        item->object = param_1;
        item->next = nullptr;
    }

    // Prepend to the object list
    item->next = node->listHead;
    node->listHead = item;
    node->count++;

    // Update event mask: set bit corresponding to object's event type
    // Object structure: +0x18 points to a type descriptor, +0x0C is the event index
    uint32_t eventType = *(uint32_t*)(*(int32_t*)((uint8_t*)param_1 + 0x18) + 0x0C);
    node->eventMask |= (1 << (eventType & 0x1F));
}