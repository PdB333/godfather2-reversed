// FUNC_NAME: LinkedListIterator::getNextOrWrap
// Function address: 0x00651610
// Retrieves the next item from a linked list iterator. If the current node is null and there are items,
// it resets the iterator to the beginning (wraps around). The iterator state is stored at this+0x14.

struct IteratorState {
    int* current;  // +0x00: pointer to current node (null if at end)
    int* start;    // +0x04: pointer to first node (for reset)
    int* end;      // +0x08: pointer to last node (or sentinel)
    int count;     // +0x0C: number of items in list
};

int LinkedListIterator::getNextOrWrap() {
    IteratorState* state = *(IteratorState**)((char*)this + 0x14);
    if (state->current != nullptr) {
        // Return data field stored at offset 0xC from the node structure
        return state->current[3];
    }
    if (state->count > 0) {
        FUN_00651a40();  // Reset/reinitialize iterator (likely sets start/end/current)
        // Note: local_c and local_8 below are uninitialized in the decompiler; they likely come from
        // the reset function or from the first node in the list. We assume they are the new current node pointer
        // and its data field after reset.
        int newCurrentPtr = local_c;   // should be set by reset
        int newData = local_8;         // should be data from the first node
        state->current = (int*)newCurrentPtr;
        state->start = (int*)newCurrentPtr;
        state->end = (int*)newCurrentPtr;
        state->count = newData;        // This overwrites count – might be a bug or different meaning
        return state->current[3];
    }
    // No items or count <=0, return whatever is in current's data field (likely 0)
    return state->current[3];
}