// FUNC_NAME: getBaseFromSelfReferencingOffset
// At 0x00643b00: Subtracts the value stored at a pointer (interpreted as an offset) from that pointer to retrieve the base of the containing structure.
int getBaseFromSelfReferencingOffset(int* ptr) {
    // ptr points to an int field that holds the byte offset from the field address to the start of the owning object.
    return (int)ptr - *ptr;
}