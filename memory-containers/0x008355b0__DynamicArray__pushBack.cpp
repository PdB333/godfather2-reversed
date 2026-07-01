// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
{
    int *data;       // actually *this is pointer to data, but we use the structure
    int size;
    int capacity;
    int newCapacity;
    undefined4 *slot;

    size = this[1];         // +0x04: current size
    capacity = this[2];     // +0x08: allocated capacity

    // If the array is full, resize
    if (size == capacity) {
        if (capacity == 0) {
            newCapacity = 1;
        }
        else {
            newCapacity = capacity * 2;   // double the capacity
        }
        // Reallocate internal buffer to new capacity
        FUN_00834f20(newCapacity);
    }

    // Write value into next slot and increment size
    slot = (undefined4 *)(*this + size * 4);   // +0x00: base pointer
    this[1] = size + 1;                        // increment size
    if (slot != (undefined4 *)0x0) {
        *slot = *value;
    }

    return;
}