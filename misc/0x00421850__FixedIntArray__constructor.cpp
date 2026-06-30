// FUNC_NAME: FixedIntArray::constructor
// Function address: 0x00421850
// Role: Constructor for FixedIntArray - allocates a fixed-size buffer of 1511 ints and initializes members.

#include <cstring>

class FixedIntArray {
public:
    // Constructor: initializes member fields and allocates array.
    // Uses ESI as 'this' pointer (fastcall-like optimization).
    void __thiscall constructor() {
        // Set capacity to 1511 (0x5e7)
        capacity_ = 0x5e7;          // +0x04
        buffer_ = nullptr;          // +0x00
        count_ = 0;                 // +0x08
        flags_ = 0;                 // +0x0C (byte)

        // Allocate memory: 0x179c bytes = 1511 * 4
        int* pBuf = reinterpret_cast<int*>(FUN_009c8e80(0x179c));
        buffer_ = pBuf;             // +0x00

        // Zero-initialize the allocated buffer
        memset(pBuf, 0, capacity_ * 4);
    }

private:
    int* buffer_;           // +0x00
    int capacity_;          // +0x04 (1511)
    int count_;             // +0x08
    unsigned char flags_;    // +0x0C
};

// Note: FUN_009c8e80 is a memory allocation routine (likely custom allocator in the engine).
int* FUN_009c8e80(int size);