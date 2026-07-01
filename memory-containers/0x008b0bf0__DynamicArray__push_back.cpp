// FUNC_NAME: DynamicArray::push_back
// Function address: 0x008b0bf0
// Role: Adds an element to the end of a dynamic array, resizing if necessary.

void __thiscall DynamicArray::push_back(int *this, undefined4 *value)
{
    int capacity = this[2]; // +0x08: capacity
    int size = this[1];     // +0x04: current size

    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate internal buffer to new capacity
        FUN_008b0020(capacity); // Likely realloc or grow function
    }

    // Write value at the end of the array
    undefined4 *dest = (undefined4 *)(this[0] + size * 4); // +0x00: data pointer
    this[1] = size + 1; // increment size
    if (dest != (undefined4 *)0x0) {
        *dest = *value;
    }
}