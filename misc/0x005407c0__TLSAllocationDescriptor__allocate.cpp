// FUNC_NAME: TLSAllocationDescriptor::allocate

struct TLSAllocationDescriptor {
    int*       basePtr;      // +0x00: pointer to start of allocated memory
    int*       endPtr;       // +0x04: normally 0, unused
    uint       sizeWithFlag; // +0x08: allocation size with 0x80000000 bit set
    int*       currentPtr;   // +0x0C: current write position (same as basePtr initially)
};

// TLS allocator structure stored per-thread
struct TLSAllocator {
    int** vtable;            // +0x00: vtable pointer
    // ... other fields ...
    byte*  currentAllocPtr;  // +0x08 (index 8): next free address in scratch buffer
    byte*  limitPtr;         // +0x2C (index 0xB): end of scratch buffer
    // Function at vtable+0x14: allocate larger memory block
};

// Thread-local storage index for allocator
extern "C" DWORD DAT_01139810;  // TLS index

// This function initializes a TLSAllocationDescriptor by allocating memory from the
// current thread's linear scratch allocator. param_1 is 'this' descriptor,
// param_2 is the number of 8-byte elements to allocate (actual size = param_2*8+16, aligned to 16).
TLSAllocationDescriptor* __thiscall TLSAllocationDescriptor::allocate(uint elementCount)
{
    TLSAllocationDescriptor* desc = this;  // param_1

    desc->basePtr      = nullptr;
    desc->endPtr       = nullptr;
    desc->sizeWithFlag = 0x80000000;   // mark as invalid initially
    desc->currentPtr   = nullptr;

    // Get the thread-local allocator
    TLSAllocator* allocator = static_cast<TLSAllocator*>(TlsGetValue(DAT_01139810));

    byte* currPos = allocator->currentAllocPtr;  // piVar2[8]
    uint  allocSize = (elementCount * 8 + 0x10) & 0xFFFFFFF0;  // align to 16 bytes

    byte* newPos = currPos + allocSize;
    if (newPos > allocator->limitPtr) {
        // Not enough space, request a new block via vtable function (offset 0x14)
        // The function takes the required size and returns a new base pointer
        typedef byte* (*ReallocFunc)(TLSAllocator*, uint);
        auto reallocFn = *reinterpret_cast<ReallocFunc*>(allocator->vtable + 3); // vtable[0x14/4] = index 5
        currPos = reallocFn(allocator, allocSize);
    } else {
        allocator->currentAllocPtr = newPos;
    }

    desc->basePtr      = reinterpret_cast<int*>(currPos);
    desc->currentPtr   = reinterpret_cast<int*>(currPos);  // same as basePtr initially
    desc->sizeWithFlag = elementCount | 0x80000000;        // store size with high bit set

    return desc;
}