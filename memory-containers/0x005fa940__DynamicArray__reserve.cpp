// FUNC_NAME: DynamicArray::reserve
class DynamicArray {
public:
    int* data;       // +0x00
    int count;       // +0x04
    int capacity;    // +0x08
};

// Reserves enough space to hold at least newCapacity elements.
// If the current capacity is already sufficient, does nothing.
// Allocates a new array, copies existing elements, and frees the old one.
void __thiscall DynamicArray::reserve(uint newCapacity) {
    if (this->capacity < newCapacity) {
        // Allocate new array of uint32 elements
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // allocateMemory
        if (this->data != nullptr) {
            uint i = 0;
            int* dst = newData;
            if (this->count != 0) {
                do {
                    if (dst != nullptr) {
                        *dst = *(int*)(this->data + i);
                    }
                    i++;
                    dst++;
                } while (i < (uint)this->count);
            }
            FUN_009c8f10(this->data); // deallocateMemory
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}