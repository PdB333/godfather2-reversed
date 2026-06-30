// FUNC_NAME: TreeNode::destroyTree
void __thiscall TreeNode::destroyTree(TreeNode* thisPtr)
{
    TreeNode* nextNode;
    
    if (thisPtr != (TreeNode *)0x0) {
        do {
            // Recursively destroy the child tree first (depth-first)
            TreeNode::destroyTree(thisPtr->child); // +0x00
            
            nextNode = thisPtr->next; // +0x04: sibling pointer
            
            // If data2 exists, call its destructor function
            if (thisPtr->data2 != 0) { // +0x20
                (*(thisPtr->data2Dtor))(thisPtr->data2); // +0x2C
            }
            
            // If data1 exists, call its destructor function
            if (thisPtr->data1 != 0) { // +0x10
                (*(thisPtr->data1Dtor))(thisPtr->data1); // +0x1C
            }
            
            // Run the node's own cleanup (likely frees the node itself)
            FUN_009c8f10(thisPtr);
            
            thisPtr = nextNode;
        } while (nextNode != (TreeNode *)0x0);
    }
    return;
}