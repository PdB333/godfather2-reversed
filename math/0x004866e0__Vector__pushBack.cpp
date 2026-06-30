// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(Vector* this, const int* value)
{
    int* buffer = this->data;
    int size = this->size;
    int capacity = this->capacity;

    // If the array is full, double its capacity (or at least 1)
    if (size == capacity)
    {
        if (capacity == 0)
        {
            capacity = 1;
        }
        else
        {
            capacity = capacity * 2;
        }
        // Reallocate the internal buffer to the new capacity
        // FUN_00486800 likely implements reallocation (new[] + copy + delete[])
        FUN_00486800(capacity);  // This function modifies this->data and this->capacity
        // After reallocation, the buffer pointer and capacity are updated by the callee
    }

    // Write the new element at the end of the array
    // this->data[this->size] = *value
    int* slot = this->data + this->size;
    *slot = *value;

    // Increment the size
    this->size = this->size + 1;
}