// FUNC_NAME: DynamicArray::push_back
void __thiscall DynamicArray::push_back(int *valuePtr) {
    // Check if capacity is full (size == capacity)
    if (size == capacity) {
        // Grow: double capacity (or set to 1 if currently 0)
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate the internal buffer to new capacity
        resize(capacity);
    }
    // Store the value at the current size index, then increment size
    data[size] = *valuePtr;
    size++;
}