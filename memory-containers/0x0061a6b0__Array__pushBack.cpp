// FUNC_NAME: Array::pushBack
// Reconstructed from 0x0061a6b0
// Adds an element (20 bytes) to the end of a dynamic array.
// Structure layout: +0x00 data pointer, +0x04 size, +0x08 capacity
// __thiscall: this in EAX

#include <cstdint>

// Forward declaration of internal reallocation function
void Array_reallocate(int newCapacity);

#pragma pack(push, 1)
struct Element20 {
    uint64_t field0;   // 8 bytes
    uint64_t field1;   // 8 bytes
    uint32_t field2;   // 4 bytes
};
#pragma pack(pop)

class Array {
public:
    void pushBack(const Element20& element) {
        // Check if capacity is exhausted
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
            Array_reallocate(newCapacity);
        }

        // Compute destination pointer
        Element20* dest = reinterpret_cast<Element20*>(data) + size;
        // Copy the element (20 bytes)
        dest->field0 = element.field0;
        dest->field1 = element.field1;
        dest->field2 = element.field2;

        size++;
    }

private:
    Element20* data;      // +0x00
    int size;             // +0x04
    int capacity;         // +0x08
};

// Stub: actual reallocation logic at 0x0061a830
void Array_reallocate(int newCapacity) {
    // Implementation not shown
}