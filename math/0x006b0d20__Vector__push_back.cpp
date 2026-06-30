// FUNC_NAME: Vector::push_back
// Function address: 0x006b0d20
// Role: Adds an element to the end of a dynamic array (vector), resizing if needed.

class Vector {
    // Offsets from 'this' (int*):
    // +0x00: data (int*) - pointer to array of elements
    // +0x04: size (int) - number of elements currently stored
    // +0x08: capacity (int) - allocated capacity (in elements)
    
    int* data;       // param_1[0]
    int size;        // param_1[1]
    int capacity;    // param_1[2]

public:
    void push_back(int* value) {  // param_2: pointer to value to copy
        int currentSize = size;
        int currentCapacity = capacity;

        if (currentSize == currentCapacity) {
            // Need to grow the array
            int newCapacity;
            if (currentCapacity == 0) {
                newCapacity = 1;
            } else {
                newCapacity = currentCapacity * 2;  // Double the capacity
            }
            // FUN_006afb30 likely reallocates the internal buffer to newCapacity
            FUN_006afb30(newCapacity);  // Resize internal storage
        }

        // Write the value at the end of the array
        int* targetSlot = data + size;  // *param_1 + param_1[1] * 4
        size = size + 1;               // Increment size
        if (targetSlot != nullptr) {
            *targetSlot = *value;       // Copy the value (4 bytes)
        }
    }
};