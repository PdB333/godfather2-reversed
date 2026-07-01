//FUNC_NAME: TransformManager::getOrCreateTransform
// Function at 0x008330e0: Retrieves or creates a TransformNode from source data, optionally linking to a parent transform.
// Uses a global ID counter and a vtable for TransformNode objects (size 0x50 = 80 bytes).
// Returns 1 on success, 0 on failure.

#include <cstdint>

// Forward declarations
class TransformNode;
class TransformManager;

// Global vtable for TransformNode objects
extern void* s_transformNodeVtable; // PTR_LAB_00d73738

// Global ID counter for TransformNode
extern int32_t g_transformNodeIdCounter; // _DAT_00d5780c

// External functions (callees)
TransformNode* findTransformNodeByKey(const int32_t* key); // FUN_0082bbb0
void* getAllocator(); // FUN_009c8f80
void initializeTransformNode(); // FUN_008334a0 (likely a constructor helper)
void registerTransformNode(TransformNode* node); // FUN_008324e0

// TransformNode structure (size 0x50)
struct TransformNode {
    void* vtable;               // +0x00
    // ... other fields up to offset 0x1c
    int32_t transformData[4];   // +0x1c (piVar4[7] to piVar4[10])
    int32_t parentTransform[4]; // +0x3c (piVar4[0xf] to piVar4[0x12])
    int32_t id;                 // +0x4c (piVar4[0x13])
};

// TransformManager class (this = param_1)
class TransformManager {
public:
    // Virtual function at vtable+0x14: checks if source data is valid
    bool isValidTransformSource(const int32_t* sourceData) const;

    // Pointer to parent transform data (offset +0x08 from this)
    int32_t* getParentTransformData() const { return *(int32_t**)(this + 2); } // param_1[2]

    // Main method: get or create a TransformNode from sourceData, optionally with additional data
    int32_t getOrCreateTransform(const int32_t* sourceData, int32_t additionalData);
};

// Implementation
int32_t TransformManager::getOrCreateTransform(const int32_t* sourceData, int32_t additionalData) {
    // Check if source data is valid via virtual function
    if (!isValidTransformSource(sourceData)) {
        return 0;
    }

    bool isNewNode = true;
    TransformNode* node = findTransformNodeByKey(sourceData);

    if (node == nullptr) {
        // Allocate a new TransformNode
        void* allocator = getAllocator();
        if (allocator == nullptr) {
            return 0;
        }
        // Call virtual allocation function on allocator (size 0x50)
        node = (TransformNode*)(*(void***)allocator)[0](allocator, 0x50); // (**(code **)*puVar5)(0x50,&stack0xfffffff0)
        if (node == nullptr) {
            return 0;
        }
        // Initialize the node
        initializeTransformNode();
        node->vtable = &s_transformNodeVtable;
        node->id = g_transformNodeIdCounter;
        isNewNode = false;
    }

    // Copy source data into node (4 ints)
    node->transformData[0] = sourceData[0];
    node->transformData[1] = sourceData[1];
    node->transformData[2] = sourceData[2];
    node->transformData[3] = sourceData[3];

    // If parent transform data exists, copy it into node
    int32_t* parentData = getParentTransformData();
    if (parentData != nullptr) {
        node->parentTransform[0] = *(parentData + 0x24 / 4); // offset 0x24
        node->parentTransform[1] = *(parentData + 0x28 / 4); // offset 0x28
        node->parentTransform[2] = *(parentData + 0x2c / 4); // offset 0x2c
        node->parentTransform[3] = *(parentData + 0x30 / 4); // offset 0x30
    }

    // If additional data provided, call virtual function on node (vtable+4)
    if (additionalData != 0) {
        (*(void(**)(TransformNode*, int32_t))(node->vtable + 4))(node, additionalData);
    }

    // If node was newly created, register it
    if (!isNewNode) {
        registerTransformNode(node);
    }

    return 1;
}