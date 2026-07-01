// FUNC_NAME: DynamicArray::push_back
// Address: 0x00835570
// Role: Appends an element to a dynamic array, resizing if necessary.

void __thiscall DynamicArray::push_back(int *this, int *value)
{
    int capacity = this[2]; // +0x08: capacity of the array
    int size = this[1];     // +0x04: current number of elements

    // If the array is full, grow it (double capacity, or set to 1 if empty)
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate internal buffer to new capacity
        FUN_00834ec0(capacity);
    }

    // Store the new value at the end of the array
    int *data = (int *)this[0]; // +0x00: pointer to element data
    data[size] = *value;
    this[1] = size + 1; // Update size
}