// FUNC_NAME: LinkedListNode::InsertAfter
void __thiscall LinkedListNode::InsertAfter(int *insertionPoint, int *tailSentinel)
{
    // This is a common linked list insertion function.
    // 'node' (this) is inserted after the location pointed to by insertionPoint.
    // insertionPoint is a pointer to a pointer to a node (typically the 'next' field of a node or the head pointer).
    // If insertionPoint points to a null pointer, tailSentinel is used as the following node for prev update.
    // Node structure: offset 0 = next (node*), offset 4 = prev (node** or node* depending on context)
    node_t *node = (node_t *)this;
    node_t *nextNode = (node_t *)*insertionPoint;   // existing next node or null
    
    node->next = nextNode;          // +0x00: set next pointer
    node->prev = (int)insertionPoint; // +0x04: store address of the pointer that points to us (for easy removal)
    
    if (nextNode == NULL) {
        nextNode = (node_t *)tailSentinel; // use sentinel if no following node
    }
    
    nextNode->prev = (int)node;     // update preceding pointer of the following node (usually points to this node)
    *insertionPoint = (int)node;    // update the link to point to the new node
}