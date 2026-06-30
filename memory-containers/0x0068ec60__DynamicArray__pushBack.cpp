// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x0068ec60
// Role: Appends an element (4 bytes) to a dynamic array, doubling capacity when full.
// Struct offsets: +0x00 = data pointer, +0x04 = current size, +0x08 = capacity
void __thiscall DynamicArray::pushBack(int *this, undefined4 *element) {
    int currentSize = this[1];           // offset +0x04
    int currentCapacity = this[2];       // offset +0x08

    if (currentSize == currentCapacity) {
        int newCapacity = (currentCapacity == 0) ? 1 : (currentCapacity * 2);
        FUN_0068e500(newCapacity);       // reallocate internal buffer
    }

    undefined4 *destination = (undefined4 *)(this[0] + currentSize * 4);
    this[1] = currentSize + 1;           // increment size

    if (destination != (undefined4 *)0x0) {
        *destination = *element;         // copy element to end of array
    }
}