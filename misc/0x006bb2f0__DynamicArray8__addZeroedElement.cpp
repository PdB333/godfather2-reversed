// FUNC_NAME: DynamicArray8::addZeroedElement
// Address: 0x006bb2f0
// Role: Adds a zero-initialized 8-byte element to a dynamic array, expanding capacity if needed. Returns pointer to the new element.

// Structure:
// +0x00: void* buffer (base pointer to allocated memory)
// +0x04: int size (current number of elements)
// +0x08: int capacity (allocated element count)

class DynamicArray8 {
public:
    void* buffer;      // +0x00
    int size;          // +0x04
    int capacity;      // +0x08

    // Reallocate the array to new capacity. (Called as FUN_006ba910)
    void reallocate(int newCapacity);

    // Add a zeroed element and return pointer to it.
    void* addZeroedElement() {
        // Check if we need to grow
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            reallocate(newCapacity);
        }

        // Compute address of new element
        int* newElement = (int*)((unsigned char*)buffer + size * 8);
        // Zero it (8 bytes)
        if (newElement != nullptr) {
            newElement[0] = 0;
            newElement[1] = 0;
        }

        // Update size and return pointer
        int oldSize = size;
        size++;
        return (unsigned char*)buffer + oldSize * 8;
    }
};