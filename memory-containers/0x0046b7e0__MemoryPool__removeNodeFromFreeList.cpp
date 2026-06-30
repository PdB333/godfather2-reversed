// FUNC_NAME: MemoryPool::removeNodeFromFreeList
// Removes a node from a singly linked free list. The node stores a pointer to the list head at +0x00
// and a pointer to the next node at +0x04. The list uses a dummy head node.
bool MemoryPool::removeNodeFromFreeList()
{
    // Get node to remove from pool (likely the next free node)
    int* node = (int*)allocateFromPool(1, &s_poolHead); // s_poolHead = global pool head at 0x00e326c8

    if (node == nullptr)
        return true; // original always returns 1

    int* listHead = (int*)*node; // +0x00: pointer to list head
    if (listHead == nullptr)
        return true;

    int* current = (int*)listHead[1]; // +0x04: first node after dummy head

    // Check if first node is the one to remove
    if (current == node)
    {
        listHead[1] = (int)node[1]; // bypass node, set head->next to node->next
        return true;
    }

    // Traverse list to find predecessor
    int* nextNode = (int*)current[1];
    while (nextNode != node)
    {
        current = (int*)current[1];
        nextNode = (int*)current[1];
    }

    // Unlink node: current->next = node->next
    current[1] = node[1];
    return true;
}