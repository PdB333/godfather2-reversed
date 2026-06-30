// FUNC_NAME: Iterator::dereference (or ListIterator::getData)
// Address: 0x00694860
// Role: Returns the data pointer of the current node in a linked list iterator.
// Asserts that the iterator is not at end (current != nullptr) and current != sentinel.

int * __thiscall Iterator::dereference(int *this) {
    // this[0] = list pointer, this[1] = current node pointer
    if (this[0] == 0) {
        FUN_00b97aea(); // Assertion: list must not be null
    }
    if (this[1] == *(int *)(this[0] + 4)) {
        FUN_00b97aea(); // Assertion: current must not be the sentinel (list->end)
    }
    return (int *)(this[1] + 0xC); // Offset 0xC = data payload within node
}