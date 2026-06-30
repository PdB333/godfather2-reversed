// FUNC_NAME: DynamicArray::copyFrom
// Address: 0x0060faa0
// Reconstructed C++: Copies array of 20-byte elements from source to this.

class DynamicArray {
public:
    // +0x00: pointer to allocated data
    int* data;
    // +0x04: number of elements currently stored
    int count;
    // +0x08: allocated capacity (max elements)
    int capacity;
};

// Forward declarations of helpers
void* allocateMemory(int size);       // FUN_009c8e80
void Element_initialize(int* ptr);    // FUN_006099f0 - initializes element at offset+8

void DynamicArray::copyFrom(const DynamicArray& source) {
    // Copy capacity and count from source
    this->capacity = source.capacity;
    this->count = source.count;

    if (this->capacity == 0) {
        this->data = 0;
        return;
    }

    // Allocate memory for capacity elements of size 0x14 (20 bytes each)
    this->data = (int*)allocateMemory(this->capacity * 0x14);

    // If source has elements, deep copy them
    if (this->count != 0) {
        int elementOffset = 0;
        for (int i = 0; i < this->count; ++i) {
            int* destElement = (int*)((char*)this->data + elementOffset);
            int* srcElement  = (int*)((char*)source.data + elementOffset);

            // Copy first 8 bytes (two ints) directly
            destElement[0] = srcElement[0];
            destElement[1] = srcElement[1];

            // Initialize remaining 12 bytes (offset +8) via copy constructor
            Element_initialize((int*)((char*)destElement + 8));

            elementOffset += 0x14;
        }
    }
}