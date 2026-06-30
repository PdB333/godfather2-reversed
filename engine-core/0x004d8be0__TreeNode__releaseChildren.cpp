// FUNC_NAME: TreeNode::releaseChildren
// Recursively releases all child nodes in a tree structure (post-order traversal).
// Offset +0x14: pointer to next child node (singly-linked list of children)
void __thiscall TreeNode::releaseChildren() {
    TreeNode* child = this->child; // +0x14: pointer to child node
    if (child != nullptr) {
        // Recursively release descendants first
        child->releaseChildren();
        // After children are released, deallocate or finalize the child node
        // Function at 0x009c8eb0 likely performs memory deallocation or cleanup
        ((void (*)(TreeNode*))0x009c8eb0)(child);
    }
}