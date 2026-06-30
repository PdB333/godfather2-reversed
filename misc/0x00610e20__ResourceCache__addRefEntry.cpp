// FUNC_NAME: ResourceCache::addRefEntry
// Function address: 0x00610e20
// Manages a hash table with linear index for resource entries.
// param_1: resource hash key
// param_2: resource ID (index into linear array)
// param_3: operation type (3 = increment reference count, other = no increment)
// Returns 1 on success (new entry created or refcount incremented), 0 on failure.

// Globals (from decompiled data references)
extern int* s_bucketArray;          // DAT_012058e0 – pointer to hash bucket heads array (0x4000 bytes)
extern uint8_t* s_linearIndexBase;  // DAT_011a0f38 – base of linear array indexed by resource ID (element stride 0x38)
extern void* allocateResourceNode(); // FUN_00610a80 – allocates a node

// Node structure (size 0x3C? at least 0x14*4 = 0x50? But offsets used: 0x0, 0x4, 0x8, 0x34, 0x38)
struct ResourceNode {
    int refCount;          // +0x00
    uint resourceID;       // +0x04 (second param)
    int operationType;     // +0x08 (third param)
    // ... padding ...
    uint key;              // +0x34 (first param hash)
    ResourceNode* next;    // +0x38 (bucket chain)
};

// Global counter at bucketArray + 0x4000
int* s_entryCount = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(s_bucketArray) + 0x4000);

int ResourceCache::addRefEntry(uint hashKey, uint resourceID, int operationType)
{
    // Invalid resource ID
    if (resourceID == 0xffffffff) {
        return 0;
    }

    // Compute bucket index from hash
    uint bucketIndex = hashKey & 0xfff;
    ResourceNode* node = reinterpret_cast<ResourceNode*>(s_bucketArray[bucketIndex]);

    // Search for existing node with matching hash key
    while (node) {
        if (node->key == hashKey) {
            break;
        }
        node = node->next;
    }

    // If node not found, allocate a new one
    if (!node) {
        ResourceNode* newNode = static_cast<ResourceNode*>(allocateResourceNode());
        if (!newNode) {
            return 0;
        }

        newNode->key = hashKey;
        newNode->refCount = 1;                // initial reference count
        newNode->resourceID = resourceID;
        newNode->operationType = operationType;

        // Insert into linear array if resource ID is in valid range (0-4095)
        if (resourceID < 0x1000) {
            // Original code: param_2 * 0x38 != -0x11a0f28 (likely overflow guard)
            // Simplified – assume valid range check
            *reinterpret_cast<ResourceNode**>(s_linearIndexBase + resourceID * 0x38) = newNode;
        }

        // Insert node at head of hash bucket
        newNode->next = reinterpret_cast<ResourceNode*>(
            s_bucketArray[bucketIndex]
        );
        s_bucketArray[bucketIndex] = reinterpret_cast<int>(newNode);

        // Increment global entry count
        (*s_entryCount)++;

        return 1;
    }

    // Node exists – only increment if operationType == 3
    if (operationType != 3) {
        return 0;
    }

    // If resource ID out of bounds, skip linear array update
    if (resourceID > 0xfff) {
        return 1;
    }

    // Access linear array entry for this resource ID
    ResourceNode** linearSlot = reinterpret_cast<ResourceNode**>(
        s_linearIndexBase + resourceID * 0x38
    );

    // Original code checks if &DAT_011a0f28 + param_2*0x38 == 0 (always false, probably a decompiler artifact)
    // We'll assume linearSlot is valid if not null
    if (!linearSlot || !*linearSlot) {
        return 1;
    }

    // Increment reference count of the node stored in linear array
    (*linearSlot)->refCount++;

    return 1;
}