// FUNC_NAME: LinkedList::insertAfter
void __thiscall LinkedList::insertAfter(int this, int newNode)
{
    int *nextNode;
    int *prevNode;

    // Get the current next node from this node's +8 offset
    nextNode = *(int **)(this + 8);
    // Set this node's next pointer to the new node
    *(int *)(this + 8) = *nextNode;
    
    // If the next node's +0x25 flag is zero, update its previous pointer
    if (*(char *)(*nextNode + 0x25) == '\0') {
        *(int *)(*nextNode + 4) = this;
    }
    
    // Set the new node's previous pointer to this node's previous
    nextNode[1] = *(int *)(this + 4);
    
    // Check if this node is the head of the list (pointed to by param_2 + 0x1c)
    if (this == *(int *)(*(int *)(newNode + 0x1c) + 4)) {
        // Update the head pointer to point to the new node
        *(int **)(*(int *)(newNode + 0x1c) + 4) = nextNode;
        *nextNode = this;
        *(int **)(this + 4) = nextNode;
        return;
    }
    
    // Get the previous node from this node's +4 offset
    prevNode = *(int **)(this + 4);
    
    // Check if this node is the tail of the list (pointed to by prevNode)
    if (this == *prevNode) {
        *prevNode = (int)nextNode;
        *nextNode = this;
        *(int **)(this + 4) = nextNode;
        return;
    }
    
    // General case: update the previous node's next pointer
    prevNode[2] = (int)nextNode;
    *nextNode = this;
    *(int **)(this + 4) = nextNode;
    return;
}