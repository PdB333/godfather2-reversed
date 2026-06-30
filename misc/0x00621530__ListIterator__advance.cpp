// FUNC_NAME: ListIterator::advance
// 0x00621530: Advances the iterator to the next node in a linked list, returning a pointer to the node's data (offset +0x10) if the list was modified since last iteration, else 0 (end of list).
// The iterator stores a saved snapshot of the current node and its next pointer on the stack (via FUN_00621b20) to detect concurrent modifications.
int __fastcall ListIterator::advance(void* thisPtr)
{
    // Saved state initialized by FUN_00621b20 (likely copies iterator fields into locals)
    int savedCurrentNode;  // local_10
    int savedNextNode;     // local_c
    FUN_00621b20(&savedCurrentNode); // initializes both locals from iterator's internal pointers

    // Current node pointer from iterator (+0x10)
    int currentNode = *(int*)((char*)thisPtr + 0x10);
    // Next pointer from the current node (+0x1c)
    int currentNext = *(int*)(currentNode + 0x1c);

    // Validate saved state vs current state
    if (savedCurrentNode == 0 || savedCurrentNode != currentNode)
    {
        FUN_00b97aea(); // assert failure (iterator invalid or list modified incorrectly)
    }

    // If the next pointer has changed (list was modified)
    if (savedNextNode != currentNext)
    {
        if (savedCurrentNode == 0)
        {
            FUN_00b97aea(); // assert failure
        }
        // If savedNextNode still equals the node's own next pointer, that means no actual change? (inconsistency)
        if (savedNextNode == *(int*)(savedCurrentNode + 0x1c))
        {
            FUN_00b97aea(); // assert failure
        }
        // Return pointer to the data offset of the new next node (+0x10 from node start)
        return savedNextNode + 0x10;
    }

    // No change: end of list reached
    return 0;
}