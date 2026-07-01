// FUNC_NAME: TLSBuffer::allocateFromTLS
// Function address: 0x00855e90
// Role: Allocate a buffer from the per-thread memory pool (TLS allocator) and initialize a TLSBuffer descriptor.
// The allocation size is elementCount * 0x30 + 0x10 (overhead for header). The TLS allocator uses a fixed-size pool.

#include <windows.h> // For TlsGetValue

// TLS allocator state structure (per-thread)
struct TLSAllocator {
    void** vtable;   // +0x00
    int field_4;     // +0x04
    int field_8;     // +0x08 current allocation position
    int field_C;     // +0x0C
    int field_10;    // +0x10
    // ... other fields ...
    int totalSize;   // +0x2C (index 0x0B * 4 = 44 decimal)
};

// TLS buffer descriptor (object being constructed)
struct TLSBuffer {
    void* mData;                // +0x00
    int mSize;                  // +0x04
    int mFlagsAndCapacity;      // +0x08, high bit = owned flag, lower bits = capacity (element count)
    void* mCurrent;             // +0x0C, often points to mData (current allocation position)
};

// Global TLS index (DAT_01139810)
extern DWORD gTlsIndex;

// __thiscall TLSBuffer constructor/init using TLS allocator
int* __thiscall TLSBuffer_allocateFromTLS(TLSBuffer* this, uint elementCount)
{
    void* allocatedBlock;
    TLSAllocator* allocator;
    uint newPosition;
    int allocationSize;
    int currentPosition;

    this->mData = NULL;
    this->mSize = 0;
    this->mFlagsAndCapacity = 0x80000000; // set owned flag initially, no capacity

    // Get per-thread allocator from TLS
    allocator = (TLSAllocator*)TlsGetValue(gTlsIndex);

    currentPosition = allocator->field_8; // current allocation offset
    allocationSize = elementCount * 0x30 + 0x10; // element size 0x30 + header overhead
    newPosition = currentPosition + allocationSize;

    // Check if allocator has enough free space
    if (newPosition > (uint)allocator->totalSize) {
        // Not enough space, call allocator's reallocation function via vtable
        // vtable at offset 0x14 is a reallocation function
        allocatedBlock = (*(void*(__thiscall**)(void*))(*allocator + 0x14))(allocationSize);
    } else {
        // Space available, advance the current position
        allocator->field_8 = newPosition;
    }

    // Update buffer descriptor
    this->mFlagsAndCapacity = elementCount | 0x80000000; // store element count with owned flag
    this->mData = allocatedBlock;
    this->mCurrent = allocatedBlock;

    return (int*)this;
}