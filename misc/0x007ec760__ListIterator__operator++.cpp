// FUNC_NAME: ListIterator::operator++
// Function at 0x007ec760: Pre-increment operator for a custom linked-list iterator.
// Checks for null container and end sentinel.

int* __thiscall ListIterator::operator++(int* thisPtr)
{
    // thisPtr points to an iterator structure:
    // +0x00: pointer to container (or manager)
    // +0x04: pointer to current node

    if (*thisPtr == 0) {
        // Error: container is null
        FUN_00b97aea(); // likely debug assertion or abort
    }

    // Read next pointer from current node at offset 0x04
    int* nextNode = *(int**)(thisPtr[1] + 4);
    thisPtr[1] = (int)nextNode; // advance iterator

    if (nextNode == *(int**)(*thisPtr + 0x18)) {
        // Error: reached end of list (container's end sentinel at +0x18)
        FUN_00b97aea();
    }

    return thisPtr; // return iterator for chaining
}