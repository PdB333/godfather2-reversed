// FUNC_NAME: TreeNode::processRecursive
void TreeNode::processRecursive(TreeNode* thisNode)
{
    char stopFlag = *(char *)((int)thisNode + 0x29); // +0x29: flag indicating stop traversal (non‑zero = stop)
    while (stopFlag == '\0')
    {
        // Recursively process the child node (at offset +0x08)
        processRecursive((TreeNode*)thisNode->child);

        // Save the next sibling pointer (at offset +0x00)
        TreeNode* nextNode = (TreeNode*)thisNode->next;

        // If there is a callback argument (at offset +0x0C), call the callback function (at offset +0x18)
        if (thisNode->callbackArg != 0)
        {
            ((void (*)(void*))thisNode->callbackFunc)(thisNode->callbackArg);
        }

        // Perform node‑specific cleanup or processing (likely releases resources)
        FUN_009c8eb0(thisNode);

        // Advance to the next sibling
        thisNode = nextNode;

        // Check the stop flag of the new node
        stopFlag = *(char *)((int)nextNode + 0x29);
    }
}