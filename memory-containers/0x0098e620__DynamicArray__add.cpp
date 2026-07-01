// FUNC_NAME: DynamicArray::add
// 0x0098e620: Adds an element to the dynamic array (push_back). Each element is 0x14 bytes.
// Structure offsets: +0x00 data pointer, +0x04 size, +0x08 capacity

void __thiscall DynamicArray::add(int* this, int* newElement) {
    int capacity = this[2]; // capacity
    if (this[1] == capacity) {
        // Need to grow the array
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        resize(newCapacity); // FUN_0098e0f0
    }

    // Calculate destination pointer: data base + size * 0x14
    int* dest = (int*)(this[0] + this[1] * 0x14);
    this[1] = this[1] + 1; // increment size

    if (dest != nullptr) {
        copyElement(dest, newElement); // FUN_004d3b50 - copy object
        dest[0x10 / 4] = newElement[0x10 / 4]; // copy field at +0x10 (4 bytes)
    }

    return;
}