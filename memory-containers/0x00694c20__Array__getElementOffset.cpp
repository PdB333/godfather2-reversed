//FUNC_NAME: Array::getElementOffset
int __fastcall Array::getElementOffset(int *this) {
    // this[0] = pointer to container (e.g., data buffer)
    // this[4] = index into the container
    // Container structure: +0x00 = data pointer? +0x04 = count (number of elements)
    // Elements are stored at offset 0x0C from the container base
    if (this[0] == 0) {
        FUN_00b97aea(); // assertion failure: null container
    }
    if (this[4] == *(int *)(this[0] + 4)) {
        FUN_00b97aea(); // assertion failure: index out of bounds (equals count)
    }
    // Return the offset from the container base to the element at the given index
    // (element size is assumed to be 1 byte, or the caller adds the container base)
    return this[4] + 0xC;
}