// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x0084af30
// Role: Adds an element to the end of a dynamically growing array.
// Structure offsets:
// +0x08: data pointer (int*)
// +0x0C: current size (int)
// +0x10: capacity (int)

struct DynamicArray {
    int* data;        // +0x08
    int size;         // +0x0C
    int capacity;     // +0x10
};

// Internal reallocation function (likely resizes the buffer)
void reallocateArray(int newCapacity);

void DynamicArray::pushBack(int value) {
    if (size == capacity) {
        // Double capacity, minimum 1
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        reallocateArray(newCap);
    }
    // Store value at current size index, then increment
    data[size] = value;
    size++;
}
```