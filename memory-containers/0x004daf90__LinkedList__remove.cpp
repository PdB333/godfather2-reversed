// FUNC_NAME: LinkedList::remove
// Address: 0x004daf90
// Removes a node from a singly linked list.
// List header: +0x4 = pointer to first node
// Each node: +0x4 = pointer to next node
void __thiscall LinkedList::remove(int nodeToRemove)
{
    int currentNode = *(int *)(this + 4);  // head node
    if (currentNode == nodeToRemove)
    {
        // Remove head: set head to nodeToRemove->next
        *(int *)(this + 4) = *(int *)(nodeToRemove + 4);
        return;
    }
    int nextNode = *(int *)(currentNode + 4);
    while (nextNode != nodeToRemove)
    {
        currentNode = nextNode;
        nextNode = *(int *)(currentNode + 4);
    }
    // Bypass the removed node
    *(int *)(currentNode + 4) = *(int *)(nodeToRemove + 4);
}