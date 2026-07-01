// FUNC_NAME: ResourceCache::addOrFindNode(ResourceUser*)
// Function address: 0x008242d0
// Identified role: Adds a resource node to the global cache or finds an existing one matching the key (4 x uint32).
// The node is then linked into the "this" object's local list (likely for reference counting or management).

#include <cstdint>

// Forward declarations for helper functions (defined elsewhere in the binary)
extern void listRemove(void* node); // FUN_004daf90 - removes a node from its list/detaches
extern void* allocateMemory(uint32_t size); // FUN_009c8e50 - custom memory allocation
extern void resizeResourceBuckets(int newCapacity); // FUN_00823ce0 - resizes the global bucket array

// Global data (static members of ResourceCache)
extern void** g_pResourceBuckets;          // DAT_0112db50 - array of bucket entries (each 8 bytes: [node*, link*])
extern uint32_t g_ResourceBucketCount;     // DAT_0112db54 - number of used buckets
extern uint32_t g_ResourceBucketCapacity;  // DAT_0112db58 - total capacity of the bucket array

// Structure of a cached resource node (size 0x28 = 40 bytes)
struct ResourceNode {
    void** vtable;      // +0x00
    void* listPrev;     // +0x04 (linked list pointer, used by listRemove)
    uint32_t key0;      // +0x08
    uint32_t key1;      // +0x0C
    uint32_t key2;      // +0x10
    uint32_t key3;      // +0x14
    // ... more fields (not used here) up to +0x27
};

// The object that requests a resource node (probably a component or manager)
class ResourceUser {
public:
    uint32_t key0;           // +0x4C
    uint32_t key1;           // +0x50
    uint32_t key2;           // +0x54
    uint32_t key3;           // +0x58
    ResourceNode* nodePtr;   // +0x5C (pointer to the resource node, used as list head)
    void* nodeListPrev;      // +0x60 (used as the "prev" pointer in the local list)
    // ... other members
};

void __thiscall ResourceCache::addOrFindNode(ResourceUser* user) {
    uint32_t i;
    for (i = 0; i < g_ResourceBucketCount; ++i) {
        ResourceNode* bucketNode = reinterpret_cast<ResourceNode*>(g_pResourceBuckets[i * 2]); // first element of bucket entry

        // Create a local sentinel to safely manipulate the node
        ResourceNode* sentinel = bucketNode;
        void* savedPrev = nullptr;
        if (bucketNode != nullptr) {
            savedPrev = bucketNode->listPrev;        // save the node's previous pointer
            bucketNode->listPrev = &sentinel;        // point node's prev to sentinel (local variable)
        }

        // Check if the node matches the requested key
        if (bucketNode != nullptr &&
            bucketNode->key0 == user->key0 &&
            bucketNode->key1 == user->key1 &&
            bucketNode->key2 == user->key2 &&
            bucketNode->key3 == user->key3)
        {
            // Found a matching node; move it from bucket to user's local list
            ResourceNode** userNodePtr = &user->nodePtr;
            if (userNodePtr != &sentinel && *userNodePtr != bucketNode) {
                if (*userNodePtr != nullptr) {
                    listRemove(userNodePtr);
                }
                *userNodePtr = bucketNode;
                if (bucketNode != nullptr) {
                    user->nodeListPrev = bucketNode->listPrev; // copy the prev pointer
                    bucketNode->listPrev = userNodePtr;         // update node's prev to point to user
                }
            }

            // Update the node's key fields (should be same as before, but just in case)
            bucketNode->key0 = user->key0;
            bucketNode->key1 = user->key1;
            bucketNode->key2 = user->key2;
            bucketNode->key3 = user->key3;

            // Cleanup: if sentinel is still pointing to a node, remove it (the node was taken)
            if (sentinel != nullptr) {
                listRemove(&sentinel);
            }
            return;
        }

        // No match: remove the sentinel (it was just a dummy) and continue
        if (sentinel != nullptr) {
            listRemove(&sentinel);
        }
    }

    // No matching node found; allocate a new one
    ResourceNode* newNode = reinterpret_cast<ResourceNode*>(allocateMemory(0x28));
    if (newNode == nullptr) {
        newNode = nullptr;
    } else {
        newNode->listPrev = nullptr;
        newNode->vtable = (void**)0x00d73438;  // static vtable pointer
        newNode->key0 = 0;
        newNode->key1 = 0;
        newNode->key2 = 0;
        newNode->key3 = 0;
        // other fields zeroed (implied by the code)
    }

    // Connect the new node into the user's local list
    ResourceNode* tempSentinel = nullptr; // local sentinel
    if (newNode != nullptr) {
        tempSentinel = static_cast<ResourceNode*>(newNode->listPrev); // Actually: newNode->listPrev was set to 0, so tempSentinel = 0? Let's see: the code does: local_c = 0; if(puVar3) local_c = puVar3[1]; puVar3[1] = &local_10; So they use a local variable as sentinel.
        // We'll follow the decompiled logic with a local sentinel variable.
    }

    ResourceNode** userNodePtr = &user->nodePtr;
    ResourceNode* localSentinel = newNode; // local_10
    if (userNodePtr != &localSentinel && *userNodePtr != newNode) {
        if (*userNodePtr != nullptr) {
            listRemove(userNodePtr);
        }
        *userNodePtr = newNode;
        if (newNode != nullptr) {
            user->nodeListPrev = newNode->listPrev;
            newNode->listPrev = userNodePtr;
        }
    }

    // Set the key fields of the new node to the user's key
    newNode->key0 = user->key0;
    newNode->key1 = user->key1;
    newNode->key2 = user->key2;
    newNode->key3 = user->key3;

    // Resize the global bucket array if needed
    if (g_ResourceBucketCount == g_ResourceBucketCapacity) {
        int newCapacity = (g_ResourceBucketCapacity == 0) ? 1 : (g_ResourceBucketCapacity * 2);
        resizeResourceBuckets(newCapacity);
    }

    // Insert the new node into the bucket array at the next available index
    void** bucketEntry = &g_pResourceBuckets[g_ResourceBucketCount * 2];
    g_ResourceBucketCount++;
    *bucketEntry = localSentinel;   // first element: node pointer
    bucketEntry[1] = nullptr;       // second element: link
    if (localSentinel != nullptr) {
        bucketEntry[1] = localSentinel->listPrev; // save previous link into bucket
        localSentinel->listPrev = reinterpret_cast<void*>(bucketEntry); // update node's prev to point to bucket entry
    }

    // Clean up the local sentinel (detach)
    if (localSentinel != nullptr) {
        listRemove(&localSentinel);
    }
}