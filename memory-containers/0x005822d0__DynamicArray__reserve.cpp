// FUNC_NAME: DynamicArray::reserve
// Address: 0x005822d0
// Role: Resizes dynamic array capacity to at least newCapacity, reallocating memory if needed.

class DynamicArray {
public:
    int* data;           // +0x00
    int count;           // +0x04
    int capacity;        // +0x08
    void* allocatorObj;  // +0x0C (nullptr → use global default)
    void* allocatorVTable; // +0x10 (points to AllocatorVTable)

    struct AllocatorVTable {
        void* (__thiscall *allocate)(size_t size, void* allocator);   // +0x00
        void (__thiscall *deallocate)(void* ptr, int flags);         // +0x04
    };

    // Global default allocator instance (address 0x01218a14)
    static void* gDefaultAllocator;

    void __thiscall reserve(uint newCapacity) {
        if (newCapacity <= (uint)capacity)
            return;

        // Select allocator
        void* alloc = allocatorObj;
        if (alloc == nullptr)
            alloc = gDefaultAllocator;

        // Get vtable functions
        AllocatorVTable* vtbl = *(AllocatorVTable**)allocatorVTable;
        void* newData = vtbl->allocate(newCapacity * sizeof(int), alloc);

        if (data != nullptr) {
            // Copy existing elements
            for (uint i = 0; i < (uint)count; ++i) {
                ((int*)newData)[i] = data[i];
            }
            // Free old block
            vtbl->deallocate(data, 0);
        }

        data = (int*)newData;
        capacity = newCapacity;
    }
};