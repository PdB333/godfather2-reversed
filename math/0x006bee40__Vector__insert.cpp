// FUNC_NAME: Vector::insert

class Vector {
public:
    int* data;      // +0x00 pointer to element array
    int size;       // +0x04 current number of elements
    int capacity;   // +0x08 allocated capacity (in elements)

    // Insert a new element slot at the given index.
    // Shifts subsequent elements right.
    // Returns pointer to the slot where the new element should be placed.
    // The element size is assumed to be sizeof(int) = 4 bytes.
    int* insert(uint index);
};

int* Vector::insert(uint index) {
    // Grow if full
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        grow(newCapacity); // FUN_006b1e10 - reallocates data to new capacity
    }

    // Pointer to one past the last element
    int* endSlot = &data[size];

    // Append case
    if (index == size) {
        size++;
        return endSlot;
    }

    // Safety check (endSlot should always be valid after resize)
    if (endSlot != nullptr) {
        // Copy the last element to the new slot (shift boundary)
        *endSlot = data[size - 1];
    }

    // Shift elements from size-2 down to index one position right
    uint i = size;
    while (i--, index < i) {
        data[i] = data[i - 1];
    }

    size++;
    return &data[index];
}