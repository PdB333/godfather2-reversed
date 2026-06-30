// FUNC_NAME: Array::pushBack
// Function address: 0x005560a0
// Role: Inserts an element (4 bytes) at the end of a dynamic array, growing the buffer if necessary.
// Structure layout:
//   +0x00 buffer (int*) - pointer to allocated element storage
//   +0x04 count (int) - current number of elements
//   +0x08 capacityFlags (int) - low 30 bits = capacity, high 2 bits = flags (e.g., ownership)

void __thiscall Array::pushBack(int *element)
{
    int capacity = this->capacityFlags & 0x3FFFFFFF;
    if (this->count == capacity)
    {
        // Grow to accommodate one more element (element size = 4 bytes)
        FUN_00aa4190(this, 4);
    }
    this->buffer[this->count] = *element;
    this->count++;
}