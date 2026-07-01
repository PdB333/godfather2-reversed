// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, int *value)
{
    int capacity = this[2]; // +0x08: capacity
    int size = this[1];     // +0x04: current size

    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate array to new capacity
        FUN_0077b420(capacity); // likely DynamicArray::reserve
    }

    int *data = (int *)this[0]; // +0x00: pointer to data
    data[size] = *value;
    this[1] = size + 1; // increment size
}