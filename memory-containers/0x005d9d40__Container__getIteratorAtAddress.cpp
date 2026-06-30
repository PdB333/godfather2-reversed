//FUNC_NAME: Container::getIteratorAtAddress
// Function address: 0x005d9d40
// Role: Creates an iterator pointing to a specific element address within a container.
// The container has element size 0x28 (40 bytes). The iterator structure is two ints:
// [0] = container pointer, [1] = current element pointer.
// param_1: output iterator (int*)
// param_2: expected container pointer for validation (0 or must equal this)
// param_3: address of the element to point to
// this: container object with fields: +0x8 = start pointer, +0xC = end pointer

void Container::getIteratorAtAddress(int* outIterator, int expectedContainer, void* elementAddress)
{
    uint start = *(uint*)(this + 8); // +0x8: start of allocated memory
    int index = 0;

    if (start != 0) {
        int sizeBytes = *(uint*)(this + 0xC) - start; // +0xC: end pointer
        int signBit = sizeBytes >> 0x1f;
        int elementCount = sizeBytes / 0x28 + signBit; // element size 0x28

        if (elementCount != signBit) { // if container is non-empty
            // Validate container state
            if (*(uint*)(this + 0xC) < start) {
                debugAssert(); // FUN_00b97aea
            }
            if ((expectedContainer != 0) && (expectedContainer != this)) {
                debugAssert(); // FUN_00b97aea
            }
            // Compute index from element address relative to start
            index = (int)(elementAddress - start) / 0x28;
            goto done;
        }
    }

    index = 0;

done:
    debugValidate(1, expectedContainer, elementAddress); // FUN_005da1d0

    start = *(uint*)(this + 8);
    if (*(uint*)(this + 0xC) < start) {
        debugAssert(); // FUN_00b97aea
    }

    uint current = start + index * 0x28; // pointer to the element at computed index

    // Bounds check
    if ((*(uint*)(this + 0xC) < current) || (current < *(uint*)(this + 0x8))) {
        debugAssert(); // FUN_00b97aea
    }

    // Fill output iterator
    outIterator[1] = current; // iterator's current pointer
    *outIterator = this;      // iterator's container pointer
    return;
}