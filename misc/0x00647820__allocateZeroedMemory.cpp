// FUNC_NAME: allocateZeroedMemory
// Address: 0x00647820
// Role: Allocates and zeroes memory from a custom heap. Used for small allocations (<=32 bytes) with optimized zeroing.
// The allocation size is determined by the product of in_EAX (passed by caller) and param_3.
// param_2 is likely a memory pool/type identifier passed to the underlying allocator.
// The function checks the block header (4 bytes before pointer) for size and flags.

#include <cstdint>
#include <cstring>

// Forward declaration of the underlying allocator function
extern "C" void* __thiscall FUN_00646620(uint32_t param2, uint32_t size, void* allocator);

void* __thiscall allocateZeroedMemory(void* thisPtr, uint32_t param2, uint32_t param3)
{
    // in_EAX is a value set by the caller before calling this function.
    // It represents the base element size or count.
    uint32_t baseSize = /* in_EAX */ 0; // Placeholder; actual value comes from register EAX
    uint32_t totalSize = baseSize * param3;

    // Call allocator
    void* block = FUN_00646620(param2, totalSize, thisPtr);
    if (block != nullptr)
    {
        uint32_t header = *((uint32_t*)block - 1); // Header right before allocated block
        uint32_t sizeField = header & 0x7FFFFFF8;  // Size field (lower 3 bits and top bit masked off)
        if ((header & 2) == 0)                     // Check flag bit (possibly 'in use' or 'type')
        {
            uint32_t usableSize = sizeField - 4;   // Usable size after subtracting header size
            if (usableSize > 0x20)                 // Large allocation: use memset
            {
                memset(block, 0, usableSize);
                return block;
            }
            // Small allocation: unrolled zeroing with fall-through switch
            if (((usableSize >> 2) - 1) < 8)       // Ensure size is in valid range (<= 36 bytes)
            {
                uint32_t* ptr = (uint32_t*)block;
                switch (sizeField)
                {
                case 0x20: // 32 bytes usable size 28
                    *ptr = 0;
                    *(ptr + 1) = 0;
                    ptr += 2;
                case 0x18: // 24 bytes usable size 20
                    *ptr = 0;
                    *(ptr + 1) = 0;
                    ptr += 2;
                case 0x10: // 16 bytes usable size 12
                    *ptr = 0;
                    *(ptr + 1) = 0;
                    ptr += 2;
                case 0x08: // 8 bytes usable size 4
                    *ptr = 0;
                }
            }
        }
    }
    return block;
}