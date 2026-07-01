// FUN_NAME: DynamicArray::insertAt
// Address: 0x008c2340
// Role: Insert element at given index in a dynamic array, return pointer to inserted slot

struct DynamicArray {
    int* data;      // +0x00
    int size;       // +0x04
    int capacity;   // +0x08
};

int* __thiscall DynamicArray::insertAt(uint index) {
    // If the array is full, resize (double or initialize to 1)
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        // Calls internal resize function (FUN_008be0b0)
        resize(newCapacity);
    }

    // If inserting at the end, just increment size and return pointer to new slot
    if (index == size) {
        size++;
        return &data[index];
    }

    // Shift elements to make room for insertion at index
    // Move the last element one position to the right
    if (data != nullptr) {
        data[size] = data[size - 1];
    }
    // Shift subsequent elements right by one
    for (uint i = size - 1; i > index; i--) {
        data[i] = data[i - 1];
    }

    size++;
    return &data[index];
}