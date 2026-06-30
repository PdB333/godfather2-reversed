// FUNC_NAME: DynamicArray::push_back
// Function at 0x006aedb0: Adds an element to the dynamic array, growing if necessary.
// Structure offsets:
//   this[0x00] = buffer (int*)
//   this[0x04] = size (int)
//   this[0x08] = capacity (int)

class DynamicArray {
public:
    int* buffer;   // +0x00
    int size;      // +0x04
    int capacity;  // +0x08

    // Adds an element to the end of the array
    void push_back(int value) {
        // Check if capacity needs to be increased
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            grow(newCapacity);  // Reallocate to new capacity (function at 0x006ad8a0)
        }
        // Store the value and update size
        buffer[size] = value;
        size++;
    }

private:
    // Reallocates the internal buffer to at least newCapacity (definition elsewhere)
    void grow(int newCapacity);
};
```