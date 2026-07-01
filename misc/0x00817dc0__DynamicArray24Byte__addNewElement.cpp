// FUNC_NAME: DynamicArray24Byte::addNewElement
// Address: 0x00817dc0
// Role: Adds a new zero-initialized element (size 0x18) to a dynamic array. Returns pointer to the new element.
// Array structure: [0x00] data pointer, [0x04] count, [0x08] capacity. Element size: 0x18 (24 bytes).

#include <cstddef>

// Forward declaration of the resize method (defined elsewhere)
// Resizes the array's capacity to newCapacity (elements), preserving existing contents.
// void DynamicArray24Byte::resizeArray(int newCapacity);

struct DynamicArray24Byte {
    int* data;      // +0x00
    int count;      // +0x04
    int capacity;   // +0x08

    // Adds a new element, zero-initializes it, returns pointer to it.
    __declspec(nothrow) int* addNewElement() {
        // If capacity is exhausted, grow the array.
        if (count == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resizeArray(newCapacity);  // calls FUN_00817000
        }

        // Pointer to the new slot at the end of the data buffer.
        int* newElement = reinterpret_cast<int*>(
            reinterpret_cast<char*>(data) + count * 0x18
        );

        // Zero-initialize the 6 ints (24 bytes) of the new element.
        if (newElement) {
            newElement[0] = 0;
            newElement[1] = 0;
            newElement[2] = 0;
            newElement[3] = 0;
            newElement[4] = 0;
            newElement[5] = 0;
        }

        // Increment count and return pointer to the newly added element.
        int oldCount = count;
        count = oldCount + 1;
        return reinterpret_cast<int*>(
            reinterpret_cast<char*>(data) + oldCount * 0x18
        );
    }

private:
    void resizeArray(int newCapacity); // implemented elsewhere (FUN_00817000)
};