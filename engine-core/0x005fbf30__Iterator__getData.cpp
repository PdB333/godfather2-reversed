// FUNC_NAME: Iterator::getData
// Address: 0x005fbf30
// Retrieves a pointer to the current element data from an iterator,
// with debug validation that the container and node are valid (non-null, not end sentinel).

// Forward declarations for container and node structures
struct ListNode;
struct Container;

// Debug assertion function (likely from engine) - called with no arguments
void DebugAssert();

// Iterator structure
struct Iterator {
    Container* mContainer;  // +0x00: pointer to the container
    ListNode*  mNode;       // +0x04: pointer to the current node

    // Returns pointer to the data stored in the current node.
    // Data starts at offset 0x08 from the node header.
    void* getData() const __thiscall {
        if (mContainer == nullptr) {
            DebugAssert();
        }
        if (mNode == reinterpret_cast<ListNode*>(reinterpret_cast<uint8_t*>(mContainer) + 0x18)) {
            DebugAssert();   // Node is the end sentinel
        }
        return reinterpret_cast<uint8_t*>(mNode) + 8;
    }
};

// Container structure (only the relevant field is shown)
struct Container {
    // ... other fields ...
    ListNode* endSentinel;  // +0x18: pointer to the sentinel node marking the end of the list
};

// Node structure (header)
struct ListNode {
    ListNode* pPrev; // +0x00: previous node
    ListNode* pNext; // +0x04: next node
    // Data follows at +0x08, structure size depends on element type
};