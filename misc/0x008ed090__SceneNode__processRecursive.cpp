// FUNC_NAME: SceneNode::processRecursive
// Address: 0x008ed090
// Role: Recursively traverses a scene node tree, processing each node that is not flagged as active.
// Structure fields:
//   +0x00: m_pNext (SceneNode*) - next sibling
//   +0x08: m_pChild (SceneNode*) - first child
//   +0x25: m_activeFlag (char) - if non-zero, skip this node and its subtree

class SceneNode {
public:
    SceneNode* m_pNext;     // +0x00
    // +0x04: unknown (int or pointer)
    SceneNode* m_pChild;    // +0x08
    // ... other fields ...
    char m_activeFlag;      // +0x25

    void __thiscall processRecursive();
};

// External functions (likely global or belonging to another class)
void processNodeTransform();              // FUN_008eb650 - probably processes global transform state
void updateNode(SceneNode* node);        // FUN_009c8eb0 - performs per-node update

void __thiscall SceneNode::processRecursive() {
    SceneNode* node = this;
    while (node->m_activeFlag == 0) {          // Continue while node is not active
        // Recursively process the first child (depth-first)
        if (node->m_pChild != nullptr) {
            node->m_pChild->processRecursive();
        }

        // Save pointer to next sibling before processing current node
        SceneNode* next = node->m_pNext;

        // Process current node
        processNodeTransform();               // Called with no arguments – may use global state
        updateNode(node);                     // Updates current node (e.g., animation, physics)

        // Move to next sibling
        node = next;
    }
}