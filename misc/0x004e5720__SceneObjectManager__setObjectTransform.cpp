// FUNC_NAME: SceneObjectManager::setObjectTransform
// Address: 0x004e5720
// Role: Looks up a scene object by hash ID in a global hash table and updates its transform data (four floats at offset 0x30-0x3c) and sets a dirty flag at offset 0x98.
// The hash table is stored in a global structure (DAT_01223398). Bucket count and bucket array are accessed through offsets.
// param_1 = object ID; param_2 = pointer to 4-float transform (e.g., quaternion + translation).

#include <cstdint>

// Global hash table base (inferred from data refs)
extern uintptr_t g_hashTableBase;  // DAT_01223398

// Node structure in linked list buckets
struct HashNode {
    uint32_t key;       // +0x00: object ID
    uintptr_t data;     // +0x04: pointer to the object's data block (scene object)
    HashNode* next;     // +0x08: next node in bucket
};

// Structure representing the hash table metadata (at g_hashTableBase+8)
struct HashTableDescriptor {
    uintptr_t bucketArrayPtr;   // +0x04? actually offset 0x4 from descriptor start?
    uint32_t bucketCount;       // +0x08 from descriptor start?
};

// Structure of a scene object (partial, only relevant fields)
struct SceneObject {
    /* ... other fields ... */
    // +0x30: transform data (4 floats)
    float transform[4];
    // +0x98: dirty/update flag
    uint8_t dirtyFlag;
};

void setObjectTransform(uint32_t id, const float transformData[4]) {
    // Navigate global hash table:
    // *(int*)(g_hashTableBase + 8) => descriptor pointer
    uintptr_t descPtr = *reinterpret_cast<uintptr_t*>(g_hashTableBase + 8);
    uintptr_t bucketArray = *reinterpret_cast<uintptr_t*>(descPtr + 4);
    uint32_t bucketCount = *reinterpret_cast<uint32_t*>(descPtr + 8);

    // Compute bucket index
    uint32_t bucketIndex = id % bucketCount;
    HashNode* node = *reinterpret_cast<HashNode**>(bucketArray + bucketIndex * 4);

    // Linear search through linked list in the bucket
    while (node != nullptr) {
        if (node->key == id) {
            // Found the node, now check if the data pointer is valid
            if (node->data != 0) {
                SceneObject* obj = reinterpret_cast<SceneObject*>(node->data);
                // Copy transform data
                obj->transform[0] = transformData[0];
                obj->transform[1] = transformData[1];
                obj->transform[2] = transformData[2];
                obj->transform[3] = transformData[3];
                // Mark as dirty
                obj->dirtyFlag = 1;
            }
            return;  // regardless of data validity, stop searching
        }
        node = node->next;
    }

    // ID not found in hash table: no valid object to update.
    // In the original code this path writes to null (likely crash or debug).
    // We leave it as a no-op for safety.
}