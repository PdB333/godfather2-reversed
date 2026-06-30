// FUNC_NAME: MemoryPool::allocateBlock
// Address: 0x004d2050
// Role: Allocate a cleared fixed-size block from a global object pool.
//       If the free list is non-empty, pop the head block. Otherwise,
//       use a factory object to allocate a new block via virtual call.
//       The block is zeroed (first 20 bytes) before return.
// Structure layout (offsets relative to global pool base at 0x012054ac):
//   +0x800c: freeListHead (pointer to next free block)
//   +0x8010: factoryParam1 (int)
//   +0x8014: factoryParam2 (int)
//   +0x8018: allocatedCount (int, current number of live blocks)
//   +0x801c: minAllocatedCount (int, running minimum)
//   +0x8020: factoryPointer (pointer to factory object with vtable)

namespace PoolAllocator {
    // Global pool base pointer (read from DAT_012054ac)
    static int*& g_poolBase = *(int**)0x012054ac;

    // Factory vtable entry: alloc function at offset +0x04
    typedef void* (__thiscall* FactoryAllocFn)(void* self, int param1, int param2);

    // Allocate a block from the pool
    void* allocateBlock() {
        int* pool = g_poolBase;
        if (pool == nullptr) {
            return nullptr;
        }

        // Try to pop from free list (offset +0x800c)
        void* block = *(void**)(pool + 0x800c / sizeof(int)); // Cast to match pointer size
        if (block != nullptr) {
            // Read next free block from the beginning of current block (first 4 bytes)
            int nextBlock = *(int*)block;
            // Update free list head
            *(int**)(pool + 0x800c / sizeof(int)) = (int*)nextBlock;

            // Decrement allocated count (+0x8018)
            int* count = (int*)((char*)pool + 0x8018);
            *count = *count - 1;

            // Update minimum count (+0x801c)
            int* minCount = (int*)((char*)pool + 0x801c);
            if ((unsigned int)*count < (unsigned int)*minCount) {
                *minCount = *count;
            }
        } else {
            // Try factory allocation if factory pointer exists (+0x8020)
            void* factory = *(void**)((char*)pool + 0x8020);
            if (factory == nullptr) {
                return nullptr;
            }
            // Retrieve vtable and call the alloc function at offset +0x04
            void** vtable = *(void***)factory;
            FactoryAllocFn allocFn = (FactoryAllocFn)vtable[1];
            int param1 = *(int*)((char*)pool + 0x8010);
            int param2 = *(int*)((char*)pool + 0x8014);
            block = allocFn(factory, param1, param2);
            if (block == nullptr) {
                return nullptr;
            }
        }

        // Zero out the block: first 20 bytes
        char* blockBytes = (char*)block;
        *(uint64_t*)blockBytes = 0;       // bytes 0-7
        *(uint64_t*)(blockBytes + 8) = 0; // bytes 8-15
        *(uint32_t*)(blockBytes + 16) = 0; // bytes 16-19

        return block;
    }
} // namespace PoolAllocator