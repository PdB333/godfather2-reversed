// FUNC_NAME: IntrusiveList::spliceRange
// Address: 0x008ee5b0
// This function moves a range of nodes [first, last) to before position within the same doubly linked list.
// The list uses a sentinel node (head) at offset 0? Actually offset 4 holds a pointer to the first node.
// Node structure: +0: next, +4: prev, +8: size? (set to 0 when list emptied)
// Parameters:
//   this (param_1): pointer to list object (contains sentinel? or first node pointer at +4)
//   output (param_2): pointer to pair of node pointers (receives the moved range [first, last))
//   first (param_3): start of range to move (inclusive)
//   last (param_4): end of range to move (exclusive)
//   position (param_5): node before which to insert the range
//   otherListEnd (param_6): end of the other list? Actually used as sentinel for iteration.
// The function asserts that first and position belong to this list (or are null).
// Special case: if last equals the node after the first node (i.e., range is entire list), it extracts the whole list.

void __thiscall IntrusiveList::spliceRange(int thisList, int* output, int first, int last, int position, int otherListEnd)
{
    int firstNext; // iVar1 - the node after first

    // Get the node after the first node (first->next)
    firstNext = **(int**)(thisList + 4); // Dereference pointer at this+4 (likely head pointer) then get its next? Actually this is confusing.
    // In the original code: iVar1 = **(int **)(param_1 + 4);
    // This reads the pointer at this+4, then dereferences it to get an int (which is a node pointer).
    // So firstNext = *(*((int*)thisList + 1))? Actually thisList+4 is a pointer to a pointer? Let's assume it's the head node's next.
    // For simplicity, we'll treat it as the first node's next.

    // Assert that first is valid (either null or belongs to this list)
    if ((first != 0) && (first != thisList)) {
        FUN_00b97aea(); // assertion failure
    }

    // Check if last equals the node after first (i.e., range is a single node? Or entire list?)
    if (last == firstNext) {
        // Special case: range is the entire list (from first to first->next)
        firstNext = *(int*)(thisList + 4); // Re-read the head pointer (first node)
        // Assert position is valid
        if ((position != 0) && (position != thisList)) {
            FUN_00b97aea();
        }
        if (otherListEnd == firstNext) {
            // Extract the entire list: make it circular with self-pointers
            FUN_008ed0d0(*(int*)(*(int*)(thisList + 4) + 4)); // Call something with head->prev? (offset 4)
            // Set head->prev = head (self)
            *(int*)(*(int*)(thisList + 4) + 4) = *(int*)(thisList + 4);
            // Clear list size (offset 8)
            *(int*)(thisList + 8) = 0;
            // Set head->next = head (self)
            *(int*)*(int*)(thisList + 4) = *(int*)(thisList + 4);
            // Set head->prev? Actually offset 8 of head? Wait: *(int *)(*(int *)(param_1 + 4) + 8) = *(int *)(param_1 + 4);
            // That sets head->prev? Let's assume offset 8 is prev.
            *(int*)(*(int*)(thisList + 4) + 8) = *(int*)(thisList + 4);
            // Return the extracted range (first, firstNext)
            *output = thisList;
            output[1] = firstNext;
            return;
        }
    }

    // General case: iterate to move nodes one by one
    while (true) {
        // Assert position is valid
        if ((position != 0) && (position != first)) {
            FUN_00b97aea();
        }
        if (last == otherListEnd) break;
        // Move one node: advance iterator and link
        FUN_008ea280(); // Probably "next" or "advance"
        FUN_008edd00((undefined1*)output, first, last); // Probably "link" or "insert"
    }

    // Return the moved range (first, last)
    *output = first;
    output[1] = last;
    return;
}