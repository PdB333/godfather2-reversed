// FUNC_NAME: DynamicArray::reserve
// Function address: 0x008b3980
// This function ensures the dynamic array has at least 'newCapacity' slots.
// If the current capacity is insufficient, it allocates a new buffer, copies existing elements,
// frees the old buffer, and updates the capacity.

struct DynamicArray {
    int* data;       // +0x00: pointer to element array
    uint size;       // +0x04: number of elements currently stored
    uint capacity;   // +0x08: allocated capacity (number of elements)
};

// External memory allocation/free functions (likely from EARS engine)
void* allocateMemory(uint size);
void deallocateMemory(void* ptr);

void __thiscall DynamicArray::reserve(uint newCapacity) {
    if (this->capacity < newCapacity) {
        // Allocate new buffer for 'newCapacity' elements (each 4 bytes)
        int* newBuffer = (int*)allocateMemory(newCapacity * 4);

        // Copy existing elements from old buffer to new buffer
        if (this->data != 0) {
            uint i = 0;
            int* dest = newBuffer;
            if (this->size != 0) {
                do {
                    if (newBuffer != 0) {
                        *dest = *(int*)(this->data + i);
                    }
                    i++;
                    dest++;
                } while (i < this->size);
            }
            // Free old buffer
            deallocateMemory(this->data);
        }

        // Update pointer and capacity
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
}