// FUNC_NAME: TreeProcessor::processNode
// Function at 0x00591ab0: Recursive processing of a tree-like node structure.
// Node data format: byte[0] = tag (0x09 for "tab" type), byte[1] = child count,
// offset 0x4 = pointer to a "tab" data structure (size + float array index),
// offset 0xC = array of child IDs (int32).
// arrayInfo: [0] = base address of a float array, [1] = array size (element count).
// When a float array element equals kSentinelFloat, it is reset to kResetFloat.
// If an index is out of bounds, DebugAssert is called.

#include <cstdint>

// Forward declaration of the debug assert function
extern void DebugAssert(int* condition);

// Constants found in the data segment
const float kSentinelFloat = *reinterpret_cast<const float*>(0x00e2b1a4);
const float kResetFloat    = *reinterpret_cast<const float*>(0x00e2b04c);

// Structure representing a node in the tree
struct TreeNode {
    char tag;          // offset 0x0
    char childCount;   // offset 0x1
    // padding (2 bytes)
    uint32_t* tabData; // offset 0x4, pointer to tab structure
    int32_t children[]; // offset 0xC, variable-length array of child IDs
};

// Structure for the "tab" data, referenced by TreeNode::tabData
struct TabData {
    int32_t unknown0; // offset 0x0
    uint32_t index;   // offset 0x4, index into the float array
};

// Structure for the array info, passed as param_4
struct ArrayInfo {
    float* base;  // [0] - pointer to float array
    uint32_t count; // [1] - number of elements in array
};

// Main recursive function
void __thiscall TreeProcessor::processNode(int childID, TreeNode* nodeData, ArrayInfo* arrayInfo) {
    // Temporarily ignore the implicit this pointer (it is not used)
    // int local_4 = reinterpret_cast<int>(this); // stored but unused

    // If the node is of "tab" type (tag == 0x09)
    if (nodeData->tag == '\t') {
        TabData* tab = reinterpret_cast<TabData*>(nodeData->tabData);
        uint32_t idx = tab->index;

        // Check bounds
        if (arrayInfo->count <= idx) {
            int zeroCondition = 0;
            DebugAssert(&zeroCondition);
        }

        // If the current value at that index is the sentinel, reset it
        if (arrayInfo->base[idx] == kSentinelFloat) {
            // Re-read index (may have changed? but same in this code)
            uint32_t idx = tab->index;
            if (arrayInfo->count <= idx) {
                int zeroCondition = 0;
                DebugAssert(&zeroCondition);
            }
            arrayInfo->base[idx] = kResetFloat;
        }
    }

    // Process children (if any)
    int numChildren = static_cast<int>(nodeData->childCount);
    if (numChildren > 0) {
        int32_t* childIds = nodeData->children;
        for (int i = 0; i < numChildren; ++i) {
            int32_t childId = childIds[i];
            // Skip if the child ID matches some special ID stored elsewhere
            // (derived from field at offset 0x7c and then 0x68 of some object)
            // It is likely a unique identifier for "self" reference to avoid recursion
            if (childId != *reinterpret_cast<int*>(*reinterpret_cast<int*>(childID + 0x7c) + 0x68)) {
                // Recursively process the child node
                // Note: childID is passed as the new "this" pointer (the object context)
                // childId is the child's ID (second parameter)
                processNode(childId, nodeData, arrayInfo);
            }
        }
    }
}