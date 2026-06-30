// FUNC_NAME: DynamicArray::reserve
// Function address: 0x005f0dc0
// This function is a member of a dynamic array container (likely similar to std::vector::reserve).
// It ensures that the capacity is at least the given value.
// If new capacity > current capacity, it allocates a new block, copies the existing elements,
// frees the old block, and updates the data pointer and capacity.

#include <cstddef> // for size_t (but using unsigned int as typical for 32-bit)

class DynamicArray {
public:
    // Member variables layout:
    // +0x00: int* data;        pointer to array of ints
    // +0x04: unsigned int count;  number of elements currently stored
    // +0x08: unsigned int capacity; allocated capacity (in elements)

    void __thiscall reserve(unsigned int newCapacity);
};

// External allocation and deallocation functions (from Ghidra: FUN_009c8e80, FUN_009c8f10)
extern "C" void* FUN_009c8e80(unsigned int size);
extern "C" void FUN_009c8f10(void* ptr);

void __thiscall DynamicArray::reserve(unsigned int newCapacity) {
    // If new capacity is greater than the current capacity
    if (newCapacity > this->capacity) {
        // Allocate memory for new capacity (size in bytes = newCapacity * sizeof(int) = newCapacity * 4)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);
        
        // If old data exists, copy the existing elements up to current count
        if (this->data != nullptr) {
            for (unsigned int i = 0; i < this->count; ++i) {
                // Safety check: newData should be non-null after allocation,
                // but the original code includes this condition.
                if (newData != nullptr) {
                    newData[i] = this->data[i];
                }
            }
            // Free old data
            FUN_009c8f10(this->data);
        }
        
        // Update data pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
    // Note: count remains unchanged.
}