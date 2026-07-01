//FUNC_NAME: DynamicArray::pushBack
// Address: 0x008c2290
// Adds an element to the end of a dynamic array, growing if necessary.

void __thiscall DynamicArray::pushBack(int *this, undefined4 value)
{
    int capacity = this[2]; // +0x08: capacity
    int size = this[1];     // +0x04: current size

    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Grow the array (reallocation function at 0x008be110)
        FUN_008be110(newCapacity);
    }

    // Write the new value at the end
    int *data = (int *)this[0]; // +0x00: pointer to element array
    data[this[1]] = value;      // store value at current size index
    this[1] = size + 1;         // increment size
}