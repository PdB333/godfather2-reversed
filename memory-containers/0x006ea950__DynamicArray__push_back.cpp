// FUNC_NAME: DynamicArray::push_back
// Address: 0x006ea950
// Role: Appends an element to a dynamic array, resizing if necessary.

void DynamicArray::push_back(int value)
{
    if (this->size == this->capacity) {
        // Double the capacity, or set to 1 if currently zero.
        int newCapacity = (this->capacity == 0) ? 1 : this->capacity * 2;
        this->grow(newCapacity);  // calls FUN_006ea5e0
    }
    // Store value at the current end of the array.
    this->data[this->size] = value;
    this->size++;
}