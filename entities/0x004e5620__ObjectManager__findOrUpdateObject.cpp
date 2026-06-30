// FUNC_NAME: ObjectManager::findOrUpdateObject
// Address: 0x004e5620
// Role: Looks up an object by ID in a hash table and updates its bounding box/position data.
//       If the object exists, copies 4 values from param_2 into its data structure at +0x30 and sets active flag at +0x98.
//       Then optionally calls a debug draw function if the Z value exceeds a global threshold.

// Global hash table manager (DAT_01223398)
extern HashTableManager* g_hashTableManager;

// Global water/ground Z threshold (DAT_00e2e210)
extern float g_waterOrGroundZThreshold;

// Forward declaration of the debug draw function (FUN_00434750)
void DebugDrawVolume(uint unknown0x178, void* volumeData, const void* label, int a4, int a5, int a6);

// Structure for hash table node
struct HashNode {
    uint m_objectId;        // +0x00
    ObjectData* m_object;   // +0x04
    HashNode* m_next;       // +0x08
};

// Structure for the object data stored
// Offset 0x30: Bounding box or position (4 floats/values)
// Offset 0x98: Active flag (byte)
struct ObjectData {
    // ... other fields ...
    float m_values01;       // +0x30
    float m_values02;       // +0x34
    float m_values03;       // +0x38
    float m_values04;       // +0x3C
    // ... other fields ...
    uint8_t m_active;       // +0x98
};

// Structure for the hash table manager accessed via global
struct HashTableManager {
    // +0x00 ?
    // +0x08: pointer to bucket table descriptor
    //   descriptor: +0x04 = bucket array, +0x08 = number of buckets (size)
    BucketTableDescriptor* m_bucketTableDescriptor; // +0x08
};

struct BucketTableDescriptor {
    // +0x04: array of pointers to HashNode (bucket heads)
    HashNode** m_buckets; // +0x04
    // +0x08: bucket count (size)
    uint m_bucketCount;   // +0x08
};

// Actual function reconstruction
void ObjectManager::findOrUpdateObject(uint objectId, const float* fourValues)
{
    // Dereference global hash table manager to get bucket descriptor
    BucketTableDescriptor* descriptor = *(BucketTableDescriptor**)((int)g_hashTableManager + 0x08);
    
    // Get bucket head for this objectId
    HashNode** buckets = *(HashNode***)((int)descriptor + 0x04);
    uint bucketCount = *(uint*)((int)descriptor + 0x08);
    uint bucketIndex = objectId % bucketCount;
    HashNode* node = buckets[bucketIndex];
    
    // Walk the linked list in this bucket
    while (node != nullptr)
    {
        if (node->m_objectId == objectId)
        {
            // Found the node
            if (node->m_object != nullptr)
            {
                // Update object data
                ObjectData* obj = node->m_object;
                obj->m_values01 = fourValues[0];
                obj->m_values02 = fourValues[1];
                obj->m_values03 = fourValues[2];
                obj->m_values04 = fourValues[3];
                obj->m_active = 1;
                
                // If the Z value (or fourth value) exceeds threshold, draw debug volume
                if (obj->m_values04 > g_waterOrGroundZThreshold)
                {
                    // Retrieve some global base pointer from thread-local storage (likely for rendering)
                    // The full chain: *( (int)(*(int*)((**(int**)(unaff_FS_OFFSET+0x2c) + 0x24)) + 0x178) )
                    void* renderContext = GetRenderContext();  // simplified
                    DebugDrawVolume(renderContext, &obj->m_values01, &LAB_004eef20, 0, 0, 0);
                }
            }
            return;
        }
        node = node->m_next;
    }
    // Object not found - in this reconstruction, we do nothing.
    // Original code potentially wrote to null address, which is probably a bug.
    // We assume the function only updates existing entries.
}
```