// FUNC_NAME: LinkedList::moveToFront
void __thiscall LinkedList::moveToFront(int this, int node)
{
    int *listNode; // pointer to the list node stored at node+0x8
    int *prevNode; // previous node in the list

    // Retrieve the list node pointer from the node's field at +0x8
    listNode = *(int **)(node + 8);
    // Update node's field to point to the next of the list node (effectively removing the list node from its position)
    *(int *)(node + 8) = *listNode;

    // If the list node's flag at +0x15 is zero, update its prev to point to the current node
    if (*(char *)(*listNode + 0x15) == '\0') {
        *(int *)(*listNode + 4) = node;
    }

    // Set the list node's next to the node's previous (disconnecting the list node from its old position)
    listNode[1] = *(int *)(node + 4);

    // Check if the node is the tail of the list (i.e., node == this->sentinel->prev)
    if (node == *(int *)(*(int *)(this + 4) + 4)) {
        // Update the sentinel's prev to point to the list node (new tail)
        *(int **)(*(int *)(this + 4) + 4) = listNode;
        // Insert the list node before the node (making node the new head)
        *listNode = node;
        *(int **)(node + 4) = listNode;
        return;
    }

    prevNode = *(int **)(node + 4);
    // Check if the node is the head of the list (i.e., node == prevNode->next)
    if (node == *prevNode) {
        // Update the previous node's next to point to the list node
        *prevNode = (int)listNode;
        // Insert the list node before the node
        *listNode = node;
        *(int **)(node + 4) = listNode;
        return;
    }

    // General case: update the previous node's third field (likely a sibling pointer) to the list node
    prevNode[2] = (int)listNode;
    // Insert the list node before the node
    *listNode = node;
    *(int **)(node + 4) = listNode;
    return;
}