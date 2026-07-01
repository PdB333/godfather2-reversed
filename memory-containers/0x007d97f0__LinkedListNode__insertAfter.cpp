// FUNC_NAME: LinkedListNode::insertAfter
int* __thiscall LinkedListNode::insertAfter(int* thisNode, int* targetNode)
{
    // Check if this node is already after targetNode
    if (*thisNode != targetNode) {
        // If this node is currently linked, remove it from its list
        if (*thisNode != 0) {
            LinkedListNode::removeFromList(thisNode); // FUN_004daf90
        }
        // Set previous pointer to targetNode (offset 0)
        *thisNode = targetNode;
        if (targetNode != 0) {
            // Set next pointer (offset 4) to targetNode's next
            thisNode[1] = *(int*)(targetNode + 4);
            // Update targetNode's next to point to this node
            *(int**)(targetNode + 4) = thisNode;
        }
    }
    return thisNode;
}