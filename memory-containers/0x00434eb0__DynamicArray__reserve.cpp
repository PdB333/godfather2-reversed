// FUNC_NAME: DynamicArray::reserve
// Address: 0x00434eb0
// Role: Ensures the array has capacity for at least 'newCapacity' elements, reallocating if necessary.

struct DynamicArray {
    uint32* data;     // +0x00
    uint32  size;     // +0x04
    uint32  capacity; // +0x08
};

// Custom memory allocation functions (likely from EA EARS allocator)
extern void* allocateMemory(uint32 size);
extern void  freeMemory(void* ptr);

void DynamicArray::reserve(uint32 newCapacity) {
    if (capacity < newCapacity) {
        uint32* newData = static_cast<uint32*>(allocateMemory(newCapacity * sizeof(uint32)));

        if (data != nullptr) {
            uint32 count = size;
            for (uint32 i = 0; i < count; ++i) {
                newData[i] = data[i];
            }
            freeMemory(data);
        }

        data = newData;
        capacity = newCapacity;
    }
}