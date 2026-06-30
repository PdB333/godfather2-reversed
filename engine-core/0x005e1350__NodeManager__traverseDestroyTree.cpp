// FUNC_NAME: NodeManager::traverseDestroyTree

void __thiscall NodeManager::traverseDestroyTree(TreeNode* node)
{
    // TreeNode structure:
    // +0x00: TreeNode* next (next sibling)
    // +0x04: ??? (unused here, possibly data/type)
    // +0x08: TreeNode* child (first child)
    // +0x15: byte enabledFlag (0 = active, non-zero = disabled/end marker)

    while (node->enabledFlag == 0)  // Traverse only active nodes
    {
        // Depth-first: process child subtree first
        traverseDestroyTree(node->child);

        // Call virtual method on this node (destructor/cleanup via vtable from manager)
        // vtable pointer stored at NodeManager+0x04 -> second entry (index 1)
        // Pass constant 0x18 (probably node size for deallocation or operation code)
        ((void (__thiscall *)(TreeNode*, int))((void**)(*(int*)(this + 4)))[1])(node, 0x18);

        // Move to next sibling
        node = node->next;
    }
}