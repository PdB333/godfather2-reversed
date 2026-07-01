// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, int *element)
{
    int currentSize = this[1]; // this->size at offset +0x04
    int currentCapacity = this[2]; // this->capacity at offset +0x08

    // If the array is full, grow it
    if (currentSize == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2; // Double capacity
        }
        // Resize/grow the underlying buffer (calls realloc equivalent)
        resizeVector(newCapacity);
    }

    // Write element at the end of the array
    int *dest = (int *)(this[0] + currentSize * 4); // this->data + size * sizeof(int)
    this[1] = currentSize + 1; // Increment size
    if (dest != (int *)0x0) {
        *dest = *element;
    }
}