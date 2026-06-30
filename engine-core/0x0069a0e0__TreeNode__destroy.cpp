// FUNC_NAME: TreeNode::destroy
// Function address: 0x0069a0e0
// Recursively destroys a tree of nodes, calling destructors on attached objects and freeing memory.

struct TreeNode {
    TreeNode* child;          // +0x00: pointer to first child node
    TreeNode* next;           // +0x04: pointer to next sibling node
    void* object1;            // +0x10: first attached object (e.g., component)
    void (*destroyObject1)(void*); // +0x1c: function pointer to destroy object1
    void* object2;            // +0x20: second attached object
    void (*destroyObject2)(void*); // +0x2c: function pointer to destroy object2
};

// Forward declaration of memory deallocation function (likely operator delete or custom free)
void deallocateNode(TreeNode* node); // FUN_009c8f10

void TreeNode::destroy(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    do {
        // Recursively destroy child subtree
        TreeNode::destroy(node->child);

        // Save pointer to next sibling before destroying current node
        TreeNode* nextNode = node->next;

        // Destroy first attached object if present
        if (node->object1 != nullptr) {
            node->destroyObject1(node->object1);
        }

        // Destroy second attached object if present
        if (node->object2 != nullptr) {
            node->destroyObject2(node->object2);
        }

        // Deallocate the current node
        deallocateNode(node);

        // Move to next sibling
        node = nextNode;
    } while (node != nullptr);
}