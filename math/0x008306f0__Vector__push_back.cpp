// FUNC_NAME: Vector::push_back
// Function address: 0x008306f0
// Role: Appends an element to a dynamic array, resizing if necessary.

class Vector {
public:
    int* data;      // +0x00: pointer to element array
    int size;       // +0x04: number of elements
    int capacity;   // +0x08: allocated capacity (in elements)

    // Reallocation function (address 0x0082b370)
    void reallocate(int newCapacity);
};

void __thiscall Vector::push_back(int* value) {
    // Check if we need to grow the array
    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        reallocate(newCapacity);
    }

    // Append the element
    int* dest = data + size;
    size++;
    if (dest != nullptr) {
        *dest = *value;
    }
}