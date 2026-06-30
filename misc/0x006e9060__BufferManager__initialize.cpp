// FUNC_NAME: BufferManager::initialize

/**
 * Function address: 0x006e9060
 * Role: Initializes a buffer manager object with a custom allocator.
 *       The buffer manages a dynamic array of data chunks (each chunk is 4 bytes?).
 *       Uses an allocator (vtable-based) to allocate the buffer memory.
 *       Also manages a separate "extra" memory block obtained from the allocator.
 */

struct BufferManager
{
    void*   data;        // +0x00: pointer to allocated buffer memory
    int     count;       // +0x04: current count (initialized to 0)
    int     elementSize; // +0x08: size of each element (parameter 2)
    void*   extra;       // +0x0C: extra block from allocator (possibly a linked list or free list)
    void*   allocator;   // +0x10: pointer to allocator object (vtable-based)
};

// Forward declaration of the allocator's virtual functions (conceptually)
// Allocator vtable layout:
//   [0] : allocate(size, base) -> returns void*
//   [2] : prepare() or reset() -> void

void* __thiscall BufferManager::initialize(BufferManager* this, int elementSize, void* allocator, int flags)
{
    this->count       = 0;                                    // +0x04
    this->elementSize = elementSize;                          // +0x08
    this->extra       = FUN_004265d0(flags, allocator);       // +0x0C: obtain extra memory block from allocator
    this->allocator   = allocator;                            // +0x10

    // Call virtual function at vtable+8 (third function) on the allocator (e.g., prepare/reset)
    (*(void (**)(void))(*(uint*)allocator + 8))();

    // Determine the base address for allocation (use extra block if available, else a global default)
    void* base = this->extra;
    if (base == nullptr)
    {
        base = &DAT_01218a14;   // Global default sentinel/buffer
    }

    // Allocate the main buffer: each element is 4 bytes? (elementSize * 4)
    // Call allocator's first virtual function (allocate)
    void* (*allocateFunc)(int, void*) = *(void* (**)(int, void*))(*(uint*)allocator);
    this->data = allocateFunc(elementSize * 4, base);        // +0x00

    return this;
}