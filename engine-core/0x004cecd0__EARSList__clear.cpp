// FUNC_NAME: EARSList::clear
// Address: 0x004cecd0
// Purpose: Clears a circular doubly-linked list by calling a virtual destructor on each node.
// The list head is at this+0x18 (6th int), count at this+0x1C (7th int).
// Each node has a vtable pointer; the second virtual function (index 1) is called with parameter 0xC (12).

void EARSList::clear()
{
    // Get pointer to the list head (circular doubly-linked list)
    int* listHead = *(int**)(this + 0x18);  // +0x18: pointer to first node (or sentinel)
    int* currentNode = *listHead;           // Dereference to get first actual node

    // Reset list head to point to itself (empty list)
    *listHead = (int)listHead;
    *(int*)(this + 0x18 + 4) = (int)listHead;  // Set prev pointer of head to itself
    *(int*)(this + 0x1C) = 0;                   // Set count to 0

    // Iterate through the list and delete each node
    if (currentNode != listHead)
    {
        do
        {
            int* nextNode = (int*)*currentNode;  // Save next pointer before deletion
            // Call virtual destructor on the node (vtable[1] with parameter 0xC)
            (**(code**)(**(int**)currentNode + 4))(currentNode, 0xC);
            currentNode = nextNode;
        } while (currentNode != listHead);
    }
}