// FUNC_NAME: ListIterator::getNextNode
// Address: 0x00621530
// Role: Advances a list iterator and returns pointer to next node's data, or 0 if at end.
// Used by many list iteration loops throughout the game (see callers list).
// Assertions (FUN_00b97aea) are debug checks ensuring iterator consistency.

int __thiscall ListIterator::getNextNode()
{
    // Call helper to initialize iterator state (sets local_10 and local_c)
    // The helper likely takes a reference to the iterator's internal buffer.
    initIterator(&local_10);

    // Retrieve current node pointer from this+0x10 and its next pointer (+0x1c)
    int* currentNode = *(int**)(this + 0x10);     // +0x10: pointer to current list node
    int* nextNode = *(int**)(currentNode + 0x1c); // +0x1c: next node pointer within node

    // Debug: validate iterator's stored current node matches the list's current node
    if (local_10 == 0 || local_10 != currentNode)
    {
        assertFailed();
    }

    // If next node pointer has changed (i.e., we can advance)
    if (local_c != nextNode)
    {
        // Debug: ensure iterator is still valid
        if (local_10 == 0)
        {
            assertFailed();
        }
        // Check that the next pointer in the stored previous node matches the actual next
        if (local_c == *(int**)(local_10 + 0x1c))
        {
            assertFailed();
        }
        // Return pointer to data at node offset +0x10 (likely the data start)
        return local_c + 0x10;
    }

    // No more nodes: end of list
    return 0;
}