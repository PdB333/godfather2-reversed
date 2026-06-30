// FUNC_NAME: ListIterator::getCurrent
// Function checks if the iterator is valid and returns pointer to data at offset 0x0C from the current node.
// param_1: pointer to iterator struct (this)
//   offset 0x00: pointer to the list sentinel (head) or container base
//   offset 0x04: pointer to the current node (which is a linked list element)
// Node layout: offset 0x00 = next, 0x04 = prev, 0x08+ = user data
int* __fastcall ListIterator::getCurrent(int *thisPtr)
{
    // Check if the list sentinel pointer is null
    if (thisPtr[0] == 0) {
        FUN_00b97aea();  // Assertion failure / crash
    }
    // Check if current node has reached the sentinel (end of list)
    if (thisPtr[1] == *(int *)(thisPtr[0] + 4)) {
        FUN_00b97aea();  // Dereferencing at end position
    }
    // Return pointer to data stored at offset 0x0C from the node
    return (int *)(thisPtr[1] + 0xC);
}