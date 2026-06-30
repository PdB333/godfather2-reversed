// FUNC_NAME: LinkedListNode::insertBefore
int* __thiscall LinkedListNode::insertBefore(int* thisNode, int* targetNode)
{
    // thisNode[0] = next pointer, thisNode[1] = prev pointer (doubly-linked list)
    if (thisNode[0] != targetNode) {
        if (thisNode[0] != 0) {
            // Remove node from its current list before inserting into new one
            unlink(thisNode);
        }
        thisNode[0] = targetNode;          // Set this node's next to target
        if (targetNode != 0) {
            thisNode[1] = targetNode[1];   // this->prev = target->prev
            targetNode[1] = thisNode;      // target->prev = this
        }
    }
    return thisNode;
}