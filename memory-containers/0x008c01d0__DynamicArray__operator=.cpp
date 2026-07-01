// FUNC_NAME: DynamicArray::operator=
int* __thiscall DynamicArray::operator=(const DynamicArray& other)
{
    // Copy capacity and size from source
    this->capacity = other.capacity;  // +0x08
    this->size = other.size;          // +0x04

    if (this->capacity == 0) {
        this->data = nullptr;         // +0x00
    } else {
        // Allocate memory for capacity elements (each 4 bytes)
        this->data = (int*)FUN_009c8e80(this->capacity * 4); // custom allocator
        // Copy size elements from source array
        for (uint i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }
    }
    return this;
}