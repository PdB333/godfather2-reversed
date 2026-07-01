// FUNC_NAME: ListIterator::getCurrentData
// Function address: 0x008eb140
// Returns a pointer to the data stored in the current node of a linked list.
// The list structure has a head pointer at offset 0 and a current node pointer at offset 4.
// Each node is assumed to have a next pointer at offset 4 (relative to node start) and data at offset 0xc.
// The function validates that the head is non-null and that the current node is not the head's next (which likely marks the end of the list).

int __fastcall ListIterator::getCurrentData(int *this)
{
    // Check that the head pointer is valid
    if (this[0] == 0) {
        FUN_00b97aea(); // Assertion or error handler (likely __debugbreak or similar)
    }
    // Check that the current node is not the head's next (sentinel or end marker)
    if (this[1] == *(int *)(this[0] + 4)) {
        FUN_00b97aea(); // Assertion or error handler
    }
    // Return pointer to the data field at offset 0xc in the current node
    return this[1] + 0xc;
}