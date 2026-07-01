// FUNC_NAME: TreeContainer::deleteSubtree

void __thiscall TreeContainer::deleteSubtree(TreeNode* node)
{
    // Recursively delete left child (offset +0x8)
    if (node->left != nullptr) {
        deleteSubtree(node->left);
    }
    // Recursively delete right child (offset +0xc)
    if (node->right != nullptr) {
        deleteSubtree(node->right);
    }
    // Call virtual destructor/release on node via vtable at this+0xc
    // vtable[1] (offset 4) takes node and a flag (0)
    NodeDestructor* destructor = *(NodeDestructor**)(this + 0xc);
    destructor->destroyNode(node, 0);
    // Decrement node count (offset +0x4)
    *(int*)(this + 4) -= 1;
}