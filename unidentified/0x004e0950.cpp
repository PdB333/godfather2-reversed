// FUN_NAME: MemoryPool::initialize
// Address: 0x004e0950
// Role: Initializes a fixed-size memory pool with 257 slots (each 4 bytes), allocating a buffer and setting active flag.

void __thiscall MemoryPool::initialize(void)
{
    // Object layout (offsets in bytes from this):
    // +0x00: int* buffer          // pointer to allocated memory
    // +0x04: int capacity         // number of slots (257)
    // +0x08: int usedCount        // currently used slots (0)
    // +0x0C: int firstFree        // index of first free slot (0)
    // +0x10: int something        // unknown (0)
    // +0x14: byte active          // flag indicating pool is active (1)
    // Note: This struct is likely larger, but only these fields are initialized here.

    this->buffer = nullptr;
    this->capacity = 0x101;                 // 257 slots
    this->usedCount = 0;
    this->firstFree = 0;
    this->something = 0;
    this->active = 1;                       // mark pool as active

    // Allocate buffer for 257 ints (0x404 bytes)
    int* newBuffer = (int*)FUN_009c8e80(0x404);   // Allocation function
    this->buffer = newBuffer;

    // Zero out the entire buffer
    _memset(newBuffer, 0, this->capacity * 4);    // capacity * sizeof(int) = 0x404
    // Further initialization (likely sets up free list or virtual functions)
    FUN_004e0e80();
}