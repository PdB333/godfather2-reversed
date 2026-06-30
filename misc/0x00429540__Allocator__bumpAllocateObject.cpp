// FUNC_NAME: Allocator::bumpAllocateObject

#include <cstdint>

// Arena structure used for bump allocation
// Global pointer at DAT_01206880 points to an instance of this struct
struct Allocator {
    uint32_t* currentPtr; // +0x14: current bump allocation pointer
    // Additional fields omitted
};

// External globals
extern Allocator* g_allocator; // DAT_01206880
extern uint32_t PTR_LAB_0110b7fc; // vtable address for allocated objects

// Allocates space from the bump allocator and initializes a fixed-size object.
// The object layout (at the allocation point) is:
//   [0x00] vtable pointer (4 bytes) -> set to PTR_LAB_0110b7fc
//   [0x04] headerValue adjusted by +0x54 if nonzero (4 bytes)
//   [0x08] padding to 16-byte alignment
//   [0x??] 16-byte data block copied from dataBlock
// After allocation, the bump pointer moves past the data block.
void Allocator::bumpAllocateObject(int headerValue, const uint64_t dataBlock[2]) {
    Allocator* alloc = g_allocator;

    // If headerValue is nonzero, add 0x54 (possibly a type offset)
    if (headerValue != 0) {
        headerValue += 0x54;
    }

    // Write vtable pointer at the current allocation position
    *(uint32_t*)(alloc->currentPtr) = reinterpret_cast<uint32_t>(&PTR_LAB_0110b7fc);

    // Advance past the vtable pointer (4 bytes)
    alloc->currentPtr = reinterpret_cast<uint32_t*>(
        reinterpret_cast<uint8_t*>(alloc->currentPtr) + 4
    );

    // Write the adjusted header value
    *alloc->currentPtr = static_cast<uint32_t>(headerValue);

    // Align the current pointer up to the next 16-byte boundary for the data
    uint32_t aligned = (reinterpret_cast<uint32_t>(alloc->currentPtr) + 0x13) & 0xFFFFFFF0;
    alloc->currentPtr = reinterpret_cast<uint32_t*>(aligned);

    // Copy 16 bytes from dataBlock to the aligned location
    uint64_t* dest = reinterpret_cast<uint64_t*>(alloc->currentPtr);
    dest[0] = dataBlock[0];
    dest[1] = dataBlock[1];

    // Advance past the 16-byte data block
    alloc->currentPtr = reinterpret_cast<uint32_t*>(
        reinterpret_cast<uint8_t*>(alloc->currentPtr) + 16
    );
}