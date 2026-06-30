// FUNC_NAME: ObjectTree::traverseTree
void __thiscall ObjectTree::traverseTree(char includeDisabled)
{
    // this+0x16: short m_childIndex (index into child array)
    // this+0x18: int* m_childArray (array of child node pointers)
    int childArray = *(int *)(this + 0x18);
    short childIndex = *(short *)(this + 0x16);
    // Get the root node of the subtree to traverse
    TreeNode* rootNode = *(TreeNode**)(childArray + childIndex * 4);

    // The double-dereference at rootNode+0x18 gives the first node in the list (iterator start)
    TreeNode* iterator = **(TreeNode***)((int)rootNode + 0x18);
    TreeNode* previousNode = rootNode; // previous node in traversal (used as stack state)

    while (true) {
        // head of the list is stored directly at rootNode+0x18 (single pointer)
        TreeNode* head = *(TreeNode**)((int)rootNode + 0x18);
        if (previousNode == 0 || previousNode != rootNode) {
            assertOrDebugBreak();   // Ensure valid traversal state
        }
        if (iterator == head) break; // Reached end of list

        if (previousNode == 0) {
            assertOrDebugBreak();
        }
        if (iterator == *(TreeNode**)((int)previousNode + 0x18)) {
            assertOrDebugBreak();   // Iterator should not be the previous node's head
        }

        // Skip nodes with flag bit 2 set (bitmask 4) unless includeDisabled is true
        if (!includeDisabled && (*(byte*)((int)iterator + 0x1C) & 4) != 0) {
            if (iterator == *(TreeNode**)((int)previousNode + 0x18)) {
                assertOrDebugBreak();
            }
            // Move to next sibling (single-linked list, next pointer at offset 0x00)
            iterator = (TreeNode*)*(int*)iterator;
        } else {
            // If node has a vtable (offset 0x18) and flag bit 0 is clear,
            // call the first virtual method with argument 1 (probably "update" or "visit")
            if (iterator->pVTable != nullptr && (*(byte*)((int)iterator + 0x1C) & 1) == 0) {
                (*(void (__thiscall**)(int))(**(int**)iterator->pVTable))(1);
            }
            // Get next (previous, iterator) pair from the traversal stack
            int* nextState = FUN_00440e30(rootNode, stackFrame, previousNode, iterator);
            previousNode = (TreeNode*)nextState[0];
            iterator = (TreeNode*)nextState[1];
        }
    }
}