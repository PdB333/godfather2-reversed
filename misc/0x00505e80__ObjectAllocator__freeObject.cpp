// FUNC_NAME: ObjectAllocator::freeObject
void ObjectAllocator::freeObject(void* object) {
    // Global allocator instance pointer (0x0120550c)
    static ObjectAllocator* s_allocator = (ObjectAllocator*)0x0120550c; // adjust as needed

    // Object identifier byte at offset +0x1D (slot index)
    uint8_t slotIndex = *(uint8_t*)((int)object + 0x1D);

    // Bitmap array entry for this slot (each slot uses 8 bytes = 64 bits)
    // Global base + slotIndex * 8 points to two 32-bit words
    uint32_t* bitmapLow  = (uint32_t*)(s_allocator + slotIndex * 8);
    uint32_t* bitmapHigh = (uint32_t*)((int)s_allocator + 4 + slotIndex * 8);

    // Compute 64-bit mask to clear (assumes __allshl shifts 1 by some value;
    // here we assume a constant mask of 0xFFFFFFFFFFFFFFFF for clearing both words)
    // Note: __allshl is a 64-bit left shift, but arguments are missing in decompilation.
    // We approximate with a full clear of the two words.
    uint64_t mask = 0xFFFFFFFFFFFFFFFFULL; // or derived from slot index
    *bitmapLow  &= ~(uint32_t)(mask);
    *bitmapHigh &= ~(uint32_t)(mask >> 32);

    // Free list management: pointer to free list header at allocator + 0x90
    struct FreeListHeader {
        void* pFirst;      // +0x00
        uint32_t blockSize; // +0x04 (not used here)
        void* pNextFree;   // +0x08? We'll use array indices below
        // ... Other fields
    };
    FreeListHeader* pool = *(FreeListHeader**)((int)s_allocator + 0x90);
    uint32_t* poolFields = (uint32_t*)pool;

    void* freeListStart = (void*)poolFields[0]; // pFirst
    if (freeListStart != nullptr) {
        // Check if object belongs to this pool's managed range
        void* poolEnd = (void*)((int)freeListStart + (int)poolFields[1]); // + size
        // If a destructor function is registered (poolFields[7] != null)
        // and object is outside the pool's managed block, call destructor
        if (poolFields[7] != 0 &&
            (object < freeListStart || poolEnd <= object)) {
            // Call virtual destructor at vtable+8
            void** vtable = *(void***)poolFields[7];
            void (*destructor)(void*) = (void (*)(void*))vtable[2]; // offset 8
            destructor(object);
            return;
        }
    }

    // Return object to free list (singly linked list via first member)
    *(uint32_t*)object = poolFields[2]; // next = current head
    poolFields[5]++;                    // free count
    poolFields[2] = (uint32_t)object;   // head = object
}