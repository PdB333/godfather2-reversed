// FUNC_NAME: EARSArray::reserve
// Function address: 0x004a7b00
// Role: Reallocate internal buffer if new capacity exceeds current capacity.
// Struct offsets: +0x00 data, +0x04 count, +0x08 capacity

#include <cstdint>

class EARSArray {
public:
    // +0x00: pointer to dynamically allocated array of uint32
    int* data;
    // +0x04: number of elements currently stored
    uint32_t count;
    // +0x08: allocated capacity (number of elements)
    uint32_t capacity;
};

void __thiscall EARSArray::reserve(uint32_t newCapacity) {
    if (this->capacity < newCapacity) {
        // Allocate new buffer for newCapacity elements (4 bytes each)
        int* newData = (int*)allocate(newCapacity * 4);  // FUN_009c8e80

        if (this->data != nullptr) {
            uint32_t i = 0;
            int* src = this->data;
            int* dst = newData;
            // Copy existing elements up to current count
            if (this->count != 0) {
                do {
                    if (dst != nullptr) {
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < this->count);
            }
            // Free old buffer
            free(this->data);  // FUN_009c8f10
        }

        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}