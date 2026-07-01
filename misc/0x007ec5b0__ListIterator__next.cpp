// FUNC_NAME: ListIterator::next

struct Node {
    Node* next; // +0x00
    // other fields follow
};

struct ListIterator {
    Node* head;   // +0x00
    Node* current; // +0x04
};

// Advances the iterator to the next node in the list.
// Asserts that the list is non-null and that we are not already at the tail.
// Returns a reference to the updated iterator (self).
ListIterator* __fastcall ListIterator::next(ListIterator* thisPtr) {
    // Ensure list head is not null
    if (thisPtr->head == nullptr) {
        FUN_00b97aea(); // assertion failure / crash
    }

    // If current pointer equals the tail node (stored at head+0x18), we are at the end.
    if (thisPtr->current == *(Node**)((unsigned char*)thisPtr->head + 0x18)) {
        FUN_00b97aea(); // assertion failure / crash
    }

    // Advance current to the next node (dereference the current node's next pointer)
    thisPtr->current = thisPtr->current->next;

    return thisPtr;
}