// FUNC_NAME: ListIterator::next
// Function: advances iterator to next node in singly linked list.
// this[0] = pointer to list header (ListHeader)
// this[1] = pointer to current node (first field is Next pointer)
// ListHeader+0x18 = tail sentinel pointer
int* __fastcall ListIterator::next(ListIterator* this)
{
    // Assert that list header is not null
    if (this->header == nullptr) {
        FUN_00b97aea(); // assertion failure
    }
    // Assert that current node is not the tail sentinel
    if (this->current == *(Node**)(this->header + 0x18)) { // suspect offset -> tail
        FUN_00b97aea(); // assertion failure
    }
    // Advance current to next node (first field is next pointer)
    this->current = (Node*)(*(size_t*)this->current);
    return this;
}