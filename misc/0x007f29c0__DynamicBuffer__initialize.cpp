// FUNC_NAME: DynamicBuffer::initialize
// Address: 0x007f29c0
// This function initializes a dynamic buffer using an allocator. It computes allocation size, calls allocator's reset, then allocates memory.
// Structure fields (offsets relative to this):
// +0x00 m_pBuffer          (void*)
// +0x04 m_flags            (int)
// +0x08 m_elementCount     (int)
// +0x0C m_adjustedAllocInfo (void*)  // result of calculateSize
// +0x10 m_pAllocator       (Allocator*)

#include <cstddef>

// Forward declaration of allocator struct
struct AllocatorVTable {
    void* (__thiscall *allocate)(Allocator* self, size_t size, void* hint); // vtable+0
    void   (__thiscall *deallocate)(Allocator* self, void* ptr);           // vtable+4
    void   (__thiscall *reset)(Allocator* self);                           // vtable+8
};

struct Allocator {
    AllocatorVTable* vtable;
};

// Global default allocator data (placeholder)
extern int g_defaultAllocator; // DAT_01218a14

// External function to compute allocation size (FUN_004265d0)
extern void* __thiscall calculateAllocationSize(int someArg, Allocator* pAllocator);

struct DynamicBuffer {
    void* m_pBuffer;               // +0x00
    int m_flags;                   // +0x04
    int m_elementCount;            // +0x08
    void* m_adjustedAllocInfo;     // +0x0C
    Allocator* m_pAllocator;       // +0x10

    // Reconstructed constructor/init method
    __thiscall DynamicBuffer* initialize(int elementCount, Allocator* pAllocator, int someArg) {
        m_flags = 0;
        m_elementCount = elementCount;
        m_adjustedAllocInfo = calculateAllocationSize(someArg, pAllocator);
        m_pAllocator = pAllocator;

        // Call allocator's reset method (vtable+8)
        pAllocator->vtable->reset(pAllocator);

        // Determine allocation hint
        void* allocHint = m_adjustedAllocInfo;
        if (allocHint == nullptr) {
            allocHint = &g_defaultAllocator;
        }

        // Allocate memory for elementCount items of size 0x14 (20 bytes each)
        m_pBuffer = pAllocator->vtable->allocate(pAllocator, elementCount * 0x14, allocHint);

        return this;
    }
};