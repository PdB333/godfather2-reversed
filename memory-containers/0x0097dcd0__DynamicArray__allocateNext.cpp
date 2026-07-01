// FUNC_NAME: DynamicArray::allocateNext
// Address: 0x0097dcd0
// Role: Allocates the next available slot in a dynamic array of 0x10-byte elements.
//        If the array is full, doubles the capacity (or sets to 1 if currently 0).
// Returns: Pointer to the newly allocated element.

class DynamicArray {
public:
    int* data;     // +0x00: pointer to element array
    int size;      // +0x04: number of elements currently stored
    int capacity;  // +0x08: maximum number of elements before reallocation

    // Allocate a new slot and return pointer to it.
    int* allocateNext() {
        if (size == capacity) {
            // Need to grow the array
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            // Reallocate internal buffer (FUN_0097bdf0)
            grow(newCapacity); // call to resize function
        }
        // Get pointer to the next free slot
        int* slot = data + (size * 4); // each element is 0x10 bytes = 4 ints
        size++;
        return slot;
    }

    // internal grow function (FUN_0097bdf0)
    void grow(int newCapacity);
};