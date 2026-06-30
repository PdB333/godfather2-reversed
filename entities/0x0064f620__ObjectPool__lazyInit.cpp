// FUNC_NAME: ObjectPool::lazyInit
void ObjectPool::lazyInit() {
    // Check if the pool has already been initialized (field at +0x1fc)
    if (*(int*)(this + 0x1fc) == 0) {
        // Reset counters at +0x200 and +0x204
        *(int*)(this + 0x200) = 0;
        *(int*)(this + 0x204) = 0;

        // Allocate a 0x1000-byte buffer (e.g., free list or bitmap) and zero it
        void* buffer1 = allocate(0x1000);
        *(void**)(this + 0x1fc) = buffer1;
        memset(buffer1, 0, 0x1000);

        // Allocate an array of 1024 elements, each 0x30 bytes (total 0xC000)
        void* elementArray = allocate(0xC000);
        if (elementArray != nullptr) {
            // Call default constructor for each element (0x400 elements, 0x30 size)
            for (int i = 0; i < 0x400; ++i) {
                new ((char*)elementArray + i * 0x30) PoolElement(); // LAB_0064f350
            }
        }
        *(void**)(this + 0x214) = elementArray;

        // Assign each element an index (stored at offset +0x28 within element)
        for (int i = 0; i < 0x400; ++i) {
            PoolElement* elem = (PoolElement*)((char*)elementArray + i * 0x30);
            elem->index = i; // offset +0x28
        }

        // Allocate a second 0x1000-byte buffer (e.g., handle array) and zero it
        void* buffer2 = allocate(0x1000);
        *(void**)(this + 0x218) = buffer2;
        // Zero out 1024 ints (0x1000 / 4)
        for (int i = 0; i < 0x400; ++i) {
            ((int*)buffer2)[i] = 0;
        }
    }
}