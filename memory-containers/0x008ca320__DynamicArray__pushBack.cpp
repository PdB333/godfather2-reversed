// FUNC_NAME: DynamicArray::pushBack

class DynamicArray {
public:
    int* data;      // +0x00
    int size;       // +0x04
    int capacity;   // +0x08

    void pushBack(int value);
};

void DynamicArray::pushBack(int value) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        // FUN_008c9f90 reallocates the array to newCapacity
        reallocate(newCapacity);
    }
    data[size] = value;
    size++;
}