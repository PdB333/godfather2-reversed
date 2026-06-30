// FUNC_NAME: LinkedList::removeNode
// Function at 0x004daf90 - Removes a node from a singly-linked list identified by a head pointer at +0x4.
// The list nodes have a 'next' pointer at offset +0x4.
// param_1: Pointer to the list object (contains head at offset 0x4)
// param_2: Pointer to the node to remove
void __thiscall LinkedList::removeNode(int listObj, int nodeToRemove)
{
    int current;
    int nextNode;

    // Get the first node from the head pointer stored at listObj+0x4
    current = *(int *)(listObj + 4); // +0x04: head pointer

    // If the head is the node to remove, just update the head to the next node
    if (current == nodeToRemove)
    {
        *(int *)(listObj + 4) = *(int *)(nodeToRemove + 4);
        return;
    }

    // Otherwise, traverse the list to find the node before nodeToRemove
    nextNode = *(int *)(current + 4); // next pointer is at +0x4 in each node
    while (nextNode != nodeToRemove)
    {
        current = *(int *)(current + 4);
        nextNode = *(int *)(current + 4);
    }

    // Remove nodeToRemove by linking the previous node to the node after it
    *(int *)(current + 4) = *(int *)(nodeToRemove + 4);
}