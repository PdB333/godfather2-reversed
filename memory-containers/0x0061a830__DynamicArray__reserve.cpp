// FUNC_NAME: DynamicArray::reserve

struct DynamicArrayElement {
    unsigned long long field0;  // +0x00
    unsigned long long field8;  // +0x08
    unsigned int field16;       // +0x10
}; // total size 0x14

class DynamicArray {
public:
    DynamicArrayElement* data;   // +0x00
    unsigned int size;           // +0x04
    unsigned int capacity;       // +0x08

    void __thiscall reserve(unsigned int newCapacity);
};

void __thiscall DynamicArray::reserve(unsigned int newCapacity) {
    // Only grow: if newCapacity > current capacity, reallocate
    if (newCapacity > this->capacity) {
        // Allocate a new block, element size = 20 bytes
        DynamicArrayElement* newData = (DynamicArrayElement*)operator new(newCapacity * sizeof(DynamicArrayElement));

        if (this->data != nullptr) {
            // Copy existing elements
            for (unsigned int i = 0; i < this->size; i++) {
                newData[i] = this->data[i];
            }
            // Free old memory
            operator delete(this->data);
        }

        this->data = newData;
        this->capacity = newCapacity;
    }
}