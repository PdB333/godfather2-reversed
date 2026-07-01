// FUNC_NAME: ListIterator::next
// Function address: 0x0081abb0
// Role: Advances the iterator to the next node in a singly-linked list with sentinel tail.
//   Stores the old iterator state (list header pointer + current node pointer) into the output parameter.
//   Validates that the list is not empty and that the current node is not the sentinel tail.
//   If validation fails, calls assertion handler FUN_0081abb0 (likely __assert or similar).
//   The list header structure has the sentinel pointer (tail) at offset 0x18.
//   ListNode structure: [next pointer (int*) at offset 0x00] [two ints of data at offsets 0x04 and 0x08? Not used here].

struct ListNode {
    ListNode* next; // +0x00 - pointer to next node
    int data0;      // +0x04 - first data field
    int data1;      // +0x08 - second data field
};

struct ListHeader {
    int unknown;    // +0x00 - possibly list size or count
    // ... padding ...
    ListNode* tail; // +0x18 - sentinel tail node pointer
};

struct ListIterator {
    ListHeader* header; // +0x00 - pointer to list header
    ListNode* current;  // +0x04 - pointer to current node
};

// __thiscall: this = param_1 (ListIterator*)
// param_2 = output pointer (ListIteratorState*)
// Returns the same output pointer parameter.
ListIteratorState* __thiscall ListIterator::next(ListIteratorState* output)
{
    ListHeader* header = this->header;
    ListNode* currentNode = this->current;

    output->header = header;
    output->currentNode = currentNode;

    if (header == 0) {
        FUN_00b97aea(); // assertion: list must be valid
    }
    if (currentNode == header->tail) {
        FUN_00b97aea(); // assertion: cannot advance past sentinel tail
    }

    // Advance to next node: currentNode = currentNode->next;
    this->current = currentNode->next;

    return output;
}