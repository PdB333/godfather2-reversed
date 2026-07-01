// FUNC_NAME: DynamicArray::pushBack

class DynamicArray {
public:
    int* data;       // +0x2c7c
    int size;        // +0x2c80
    int capacity;    // +0x2c84
};

// Reallocation function (address 0x007848a0)
void __thiscall reallocate(int newCapacity);

void __thiscall DynamicArray::pushBack(int value) {
    // Grow the array if full
    if (this->size == this->capacity) {
        int newCapacity = (this->capacity == 0) ? 1 : this->capacity * 2;
        reallocate(newCapacity);
    }
    // Store the new element at the end
    this->data[this->size] = value;
    this->size++;
}