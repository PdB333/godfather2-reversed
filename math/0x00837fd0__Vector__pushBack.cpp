// FUNC_NAME: Vector::pushBack

void __thiscall Vector::pushBack(int *this, undefined4 *element)
{
    int *dataPtr;
    int currentSize;
    int currentCapacity;
    int newCapacity;

    currentSize = this[1]; // +0x04: m_size
    currentCapacity = this[2]; // +0x08: m_capacity

    if (currentSize == currentCapacity) {
        // Need to grow the array
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        // Reallocate internal buffer to new capacity
        grow(newCapacity);
    }

    // Write element at the end of the array
    dataPtr = (int *)(*this + currentSize * 4); // *this is m_data (pointer to array)
    this[1] = currentSize + 1; // Increment size
    if (dataPtr != (int *)0x0) {
        *dataPtr = *element;
    }
    return;
}