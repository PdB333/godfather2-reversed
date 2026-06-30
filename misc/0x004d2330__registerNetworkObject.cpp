// FUNC_NAME: registerNetworkObject

// Function at 0x004d2330: Registers an object (or checks if already registered) into a global hash table.
// The object's key is at offset +0x30, and the hash table base is stored at DAT_012054ac.
// The hash table has 0x2000 slots, each a linked list of nodes. A counter at +0x8000 tracks total nodes.

#include <cstdint>

// Forward declarations (assume these exist elsewhere)
struct NetworkObject;          // The object type with field at +0x30 as uint32_t key
struct HashTableNode;          // Node in the hash table: {uint32_t flags; uint32_t unused; NetworkObject* pObj; uint32_t key; HashTableNode* pNext;}
void* allocateNode();          // FUN_004d2050, likely returns a HashTableNode*
void LOCK();                   // Critical section lock
void UNLOCK();                 // Critical section unlock

// Global hash table base pointer (exported symbol DAT_012054ac)
// Structure: offset 0-0x7FFC: array of 0x2000 pointers (HashTableNode*)
//            offset 0x8000: uint32_t nodeCount
extern uint8_t* g_pHashTableBase;

int registerNetworkObject(NetworkObject* pObject)
{
    if (pObject == nullptr)
        return 0;

    uint32_t key = *(uint32_t*)((uint8_t*)pObject + 0x30);  // +0x30: network ID / hash key

    // Compute bucket index (0x1fff mask, i.e., 13 bits)
    uint32_t bucketIndex = key & 0x1fff;

    // Get head of the linked list for this bucket
    HashTableNode** ppBucketHead = (HashTableNode**)(g_pHashTableBase + bucketIndex * 4);
    HashTableNode* pNode = *ppBucketHead;

    // Search the list for an existing node with the same key
    while (pNode != nullptr)
    {
        if (pNode->key == key)
        {
            // Already registered
            return 1;
        }
        pNode = pNode->pNext;  // +0x10: next pointer
    }

    // Not found, allocate a new node
    HashTableNode* pNewNode = (HashTableNode*)allocateNode(); // FUN_004d2050
    if (pNewNode == nullptr)
        return 0;

    // Set key
    pNewNode->key = key;                                  // +0x0C (puVar3[3])

    // Lock and set flags (possibly a "dirty" or "active" flag)
    LOCK();
    pNewNode->flags = 1;                                   // +0x00 (puVar3[0])
    UNLOCK();

    // Store object pointer
    pNewNode->pObject = pObject;                           // +0x08 (puVar3[2])

    // Lock and set unused field (maybe previous/next in free list)
    LOCK();
    pNewNode->unused = 0;                                  // +0x04 (puVar3[1])
    UNLOCK();

    // Insert at head of bucket list
    pNewNode->pNext = *ppBucketHead;                       // +0x10 (puVar3[4])
    *ppBucketHead = pNewNode;

    // Increment global node count
    uint32_t* pNodeCount = (uint32_t*)(g_pHashTableBase + 0x8000);
    (*pNodeCount)++;

    return 1;
}