// FUNC_NAME: ListIterator::operator-> (or dereference)
// Iterates over a linked list node, returning pointer to data at offset 8 from node.
// Asserts that the iterator is not null and not at the end (end sentinel stored at container+0x18).
int* __fastcall ListIterator::operator->(ListIterator* this) {
    if (this->mContainer == 0) {
        _assert(); // FUN_00b97aea — assertion failure
    }
    if (this->mNode == *(int**)(this->mContainer + 0x18)) { // end sentinel
        _assert();
    }
    return (int*)(this->mNode + 8); // data starts at node+8 (after prev/next pointers)
}

// Layout:
// ListIterator:
//   +0x00: mContainer (List*)
//   +0x04: mNode (Node*)
// Node:
//   +0x00: prev (Node*)
//   +0x04: next (Node*)
//   +0x08: data (ValueType)