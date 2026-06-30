// FUNC_NAME: Bitmap::createFromSource
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Function at 0x006659c0
// EARS bitmap subsystem: creates a new bitmap from an existing source, storing a handle.
// __thiscall with 'this' pointing to a bitmap descriptor (contains size at +0x00 and source data pointer at +0x0C).
// param_1: pointer to requested element count (uint32)
// param_2: pointer to a 16-byte handle (two uint64_t) that will be overwritten; the old handle content is freed.
// Returns: 0 on success, -2 on allocation failure, or error code from FUN_00665ce0 (likely bitmap initializer).

int __thiscall Bitmap::createFromSource(int* pRequestedCount, uint64_t* outHandle)
{
    uint32_t* newBitmap;        // allocated buffer for bitmap data (each element is uint32_t)
    uint32_t newCount;          // number of elements to copy (min of this->count and pRequestedCount)
    int initResult;             // result from FUN_00665ce0
    int i;                      // loop index, also used for zeroing below after break
    uint64_t oldHandleMagic;    // first 8 bytes of old handle (holds size in low 32 bits)
    void* oldBitmapPtr;         // pointer extracted from old handle (stored in high 32 bits of second uint64)

    // Determine the number of elements to process: min(this->count, *pRequestedCount)
    // this->count is stored at offset 0x00 of the 'this' object
    if (*this < *pRequestedCount) {
        newCount = *this;
    } else {
        newCount = *pRequestedCount;
    }

    // Allocate a new bitmap buffer: 4 * 0x40 = 256 bytes (64 uint32_t elements)
    newBitmap = (uint32_t*)_calloc(4, 0x40);
    if (newBitmap == nullptr) {
        return -2;
    }

    // Initialize the new bitmap (likely sets all bits or applies a default pattern)
    initResult = FUN_00665ce0();   // E.g., Bitmap::initDefault or similar
    if (initResult != 0) {
        return initResult;
    }

    // Copy the source bitmap data by AND-ing with the new bitmap
    // Source bitmap pointer is at this[3] (offset 0x0C from this)
    for (i = 0; i < (int)newCount; i++) {
        newBitmap[i] = newBitmap[i] & ((uint32_t*)this[3])[i];
    }

    // If the loop terminated early (negative count), zero remaining elements
    if (i < 0) {
        uint32_t* clearPtr = (uint32_t*)((uint8_t*)newBitmap + i * 4);
        for (int j = -i; j != 0; j--) {
            *clearPtr = 0;
            clearPtr++;
        }
    }

    // Preserve old handle values for cleanup
    oldHandleMagic = outHandle[0];
    // Extract pointer from old handle: high 32 bits of the second uint64
    oldBitmapPtr = (void*)(uintptr_t)(outHandle[1] >> 32);

    // Store new handle:
    //  outHandle[0] = magic value + size? Actually the decomp stores 0x4000000000 directly.
    //  The old handle's first 8 bytes held the element count in its low 32 bits; the new handle
    //  replaces that with a constant magic (0x4000000000) – this magic may encode type info.
    //  outHandle[1] = pointer packed into high 32 bits (low 32 bits zero).
    outHandle[0] = 0x4000000000ULL;
    outHandle[1] = (uint64_t)(uintptr_t)newBitmap << 32;

    // Free the old bitmap if it existed
    if (oldBitmapPtr != nullptr) {
        // The old handle's first 8 bytes stored the size in its low 32 bits
        int oldSize = (int)(uint32_t)oldHandleMagic;
        _memset(oldBitmapPtr, 0, oldSize * 4);
        _free(oldBitmapPtr);
    }

    return 0;
}