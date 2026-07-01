// FUNC_NAME: DynamicArray::reserve
// Function address: 0x0084ac30
// Role: Ensures the dynamic array has capacity for at least 'capacity' elements.
//       If current capacity is smaller, allocates new memory, copies existing elements,
//       frees old memory, and updates capacity. The element count remains unchanged.
// Fields: +0x00 data pointer, +0x04 count, +0x08 capacity

class DynamicArray {
public:
    int* data;      // offset +0x00
    int count;      // offset +0x04
    int capacity;   // offset +0x08

    // __thiscall
    void __thiscall reserve(uint newCapacity) {
        if (this->capacity < newCapacity) {
            // Allocate new block with size newCapacity * sizeof(int)
            int* newData = (int*)operator new[](newCapacity * 4);
            if (this->data != nullptr) {
                uint i = 0;
                int* dst = newData;
                if (this->count != 0) {
                    do {
                        if (newData != nullptr) {
                            *dst = this->data[i];
                        }
                        i++;
                        dst++;
                    } while (i < (uint)this->count);
                }
                operator delete[](this->data);
            }
            this->data = newData;
            this->capacity = newCapacity;
        }
    }

    // forward declarations of memory allocation/free functions (not defined here)
    void* operator new[](size_t size);
    void operator delete[](void* ptr);
};