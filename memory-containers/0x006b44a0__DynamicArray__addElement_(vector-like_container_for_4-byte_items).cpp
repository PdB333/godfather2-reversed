// FUNC_NAME: DynamicArray::addElement (vector-like container for 4-byte items)
void __thiscall DynamicArray::addElement(int *this, undefined4 *element)
{
    int capacity = this[2]; // +0x08: capacity
    int count = this[1];    // +0x04: current count
    int *data = (int *)this[0]; // +0x00: pointer to element array

    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // FUN_006b1e10: reallocate internal array to new capacity
        resize(capacity);
    }

    // Store the element at the current end position
    data[count] = (int)*element;
    this[1] = count + 1; // increment count
}