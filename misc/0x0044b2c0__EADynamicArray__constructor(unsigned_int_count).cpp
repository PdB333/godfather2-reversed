// FUNC_NAME: EADynamicArray::constructor(unsigned int count)
void __thiscall EADynamicArray::constructor(uint count)
{
    // Allocate memory for 'count' elements, each 8 bytes.
    void* data = allocateMemory(count * 8);
    if (data != nullptr) {
        // Call the default constructor for each element (8 bytes each).
        // The constructor function pointer at LAB_00449ee0 is used.
        vector_constructor_iterator(data, 8, count, &elementConstructor);
    } else {
        data = nullptr; // Explicit null assignment (redundant, but preserved from original)
    }

    // Initialize the dynamic array structure fields.
    // +0x00: pointer to allocated data
    this->data = data;
    // +0x04: number of elements (size)
    this->size = count;
    // +0x08: capacity (initially 0, likely set separately later)
    this->capacity = 0;
    // +0x0C: flags or other state
    this->flags = 0;
}