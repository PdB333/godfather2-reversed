// FUNC_NAME: DynamicArray::insertAt
// Function at 0x0096aef0 inserts an element at the given index, shifting subsequent elements to the right.
// Assumes contiguous storage; grows capacity if full (doubles or sets to 1 if capacity was 0).
// Returns pointer to the slot where the new element should be placed.
// The caller is expected to write the new element into the returned pointer.

#include <cstdint>

// Forward declaration of internal reallocation function (FUN_00963c10)
void reallocate(int newCapacity);  // Not defined here; likely modifies the array's internal buffer

int* DynamicArray::insertAt(uint32_t index)
{
    // Layout: this[0] -> pointer to data buffer
    //         this[1] -> current size (number of elements)
    //         this[2] -> current capacity

    int* data       = reinterpret_cast<int*>(this[0]);
    uint32_t size   = this[1];
    uint32_t cap    = this[2];

    // Grow if full
    if (size == cap) {
        uint32_t newCap = (cap == 0) ? 1 : cap * 2;
        reallocate(newCap);   // Likely sets this[0] and this[2] accordingly
        // After reallocation, data pointer must be re-read, but size is unchanged
        data = reinterpret_cast<int*>(this[0]);
        cap  = this[2];
    }

    uint32_t newSize = size;  // will be used for shifting

    // If appending at the end, just increment size and return pointer to new slot
    if (index == size) {
        this[1] = size + 1;
        return &data[index];
    }

    // Extend array by copying the last element one position to the right
    // This makes room for the shift that follows.
    int* endSlot = &data[size];   // slot AFTER the last element (now valid if capacity >= size+1)
    if (endSlot != nullptr) {     // always true unless buffer is null
        *endSlot = data[size - 1];
    }

    // Shift elements from size-1 down to index+1 to the right
    // Note: after the previous copy, data[size] holds the old last element.
    uint32_t i = size;
    while (i = i - 1, index < i) {
        data[i] = data[i - 1];
    }

    // Update size
    this[1] = size + 1;

    // Return pointer to slot at index (now empty, ready for new element)
    return &data[index];
}