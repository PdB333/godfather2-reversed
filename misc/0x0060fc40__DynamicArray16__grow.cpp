// FUNC_NAME: DynamicArray16::grow

// Function: void DynamicArray16::grow(uint newCapacity)
// Address: 0x0060fc40
// Description: Resizes internal buffer to new capacity (if larger) and copies existing elements.
// Element size: 0x10 (16 bytes)
// Class layout: offset+0x00: data* (pointer to array of 16-byte elements)
//               offset+0x04: count (uint)
//               offset+0x08: capacity (uint)
// Functions: FUN_009c8e80 = operator new[] or custom allocate, FUN_009c8f10 = operator delete[] or custom free

#include <cstdint>

class DynamicArray16 {
public:
    void* data;        // +0x00
    uint32_t count;    // +0x04
    uint32_t capacity; // +0x08

    // Assumes __thiscall calling convention
    void grow(uint32_t newCapacity);
};

void DynamicArray16::grow(uint32_t newCapacity) {
    if (this->capacity < newCapacity) {
        // Allocate new buffer: newCapacity * 16 bytes
        uint64_t* newData = reinterpret_cast<uint64_t*>(FUN_009c8e80(newCapacity << 4)); // allocate(newCapacity * 16)
        
        // Copy existing elements (each 16 bytes = 2 uint64_t)
        if (this->data != nullptr && this->count > 0) {
            uint32_t i = 0;
            uint64_t* src = reinterpret_cast<uint64_t*>(this->data);
            uint64_t* dst = newData;
            do {
                if (dst != nullptr) {
                    *dst = *src;              // Copy first 8 bytes
                    *(dst + 1) = *(src + 1);  // Copy next 8 bytes
                }
                i++;
                src += 2; // Move by 16 bytes
                dst += 2;
            } while (i < this->count);
        }
        
        // Free old buffer
        FUN_009c8f10(this->data); // free(oldData)
        
        // Update members
        this->data = reinterpret_cast<void*>(newData);
        this->capacity = newCapacity;
    }
}