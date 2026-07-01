// FUNC_NAME: DynamicArray::ensureCapacity

// Reconstructed struct for dynamic array (EA EARS): 
// +0x00: int* data (pointer to element array)
// +0x04: uint32_t size (number of elements currently stored)
// +0x08: uint32_t capacity (allocated element count)

struct DynamicArray {
    int* data;
    uint32_t size;
    uint32_t capacity;
};

// Memory allocation helpers (wrappers around new[]/malloc)
extern void* allocate(uint32_t bytes);
extern void deallocate(void* ptr);

// Ensure the array has capacity for at least newCapacity elements.
// If current capacity is insufficient, reallocate a larger buffer.
void __thiscall DynamicArray::ensureCapacity(uint32_t newCapacity) {
    if (this->capacity < newCapacity) {
        int* newData = (int*)allocate(newCapacity * sizeof(int));
        if (this->data != nullptr) {
            for (uint32_t i = 0; i < this->size; i++) {
                if (newData != nullptr) {
                    newData[i] = this->data[i];
                }
            }
            deallocate(this->data);
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}