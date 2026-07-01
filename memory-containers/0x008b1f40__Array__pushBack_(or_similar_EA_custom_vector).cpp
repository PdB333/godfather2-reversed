// FUNC_NAME: Array::pushBack (or similar EA custom vector)
// Address: 0x008b1f40
// This function adds an element to a dynamic array, doubling capacity if needed.

class Array {
public:
    int* data;       // +0x00: pointer to element array
    int size;        // +0x04: current number of elements
    int capacity;    // +0x08: allocated capacity (in elements)

    // Internal reallocation function (FUN_008b1a50) grows the array
    void grow(int newCapacity);

    // Push a value onto the end of the array
    void __thiscall pushBack(int* value) {
        if (size == capacity) {
            // Capacity exhausted – double it (or set to 1 if zero)
            int newCap = (capacity == 0) ? 1 : capacity * 2;
            grow(newCap);
        }
        // Store value at current end and increment size
        data[size] = *value;
        size++;
    }
};