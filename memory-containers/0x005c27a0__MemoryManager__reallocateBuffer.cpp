// FUNC_NAME: MemoryManager::reallocateBuffer
// Address: 0x005c27a0
// Reallocates an array of elements using a custom memory manager (vtable at 0x012234ec).
// Growth strategy: newCapacity = (capacity != 0) ? capacity + 5 : 0;
// If newCapacity < elementCount, newCapacity = elementCount.
// Returns the new buffer pointer on success. On reallocation (move), copies old data,
// frees old buffer, and stores the new capacity via outNewCapacity.
// Note: This is a static helper function; the memory manager is accessed globally.

#include <cstddef>
#include <cstring>

// Forward declarations for the global memory manager vtable
struct MemoryManagerVTable {
    void* (*alloc)(size_t size, void* out[2]);   // returns pointer, sets out[0]=oldPtr, out[1]=errorCode
    void  (*free)(void* ptr, int flags);
};

extern MemoryManagerVTable* gMemoryManager;  // Actually DAT_012234ec points to the vtable pointer

// Reconstructed function
void* MemoryManager::reallocateBuffer(
    int& outNewCapacity,        // [out] new capacity (written only on reallocation)
    int& elementCount,          // [in/out] current number of stored elements
    size_t elementSize,         // size of each element
    int flags,                  // allocation flags (passed to alloc/free)
    int& capacity               // [in/out] current maximum capacity in elements
)
{
    // Determine new capacity
    int newCapacity = (capacity != 0) ? capacity + 5 : 0;
    if (newCapacity < elementCount) {
        newCapacity = elementCount;
    }

    // Local variables used by the alloc call (output structure)
    void* oldBuffer = nullptr;     // local_4
    int   errorCode = 0;           // local_c (unused)

    // Allocate new buffer via memory manager vtable
    void* newBuffer = gMemoryManager->alloc(newCapacity * elementSize, &oldBuffer);

    // Check if allocation caused a move (oldBuffer != 0)
    if (oldBuffer == nullptr) {
        // No reallocation (first allocation or in-place resize)
        capacity = newCapacity;
        return newBuffer;
    }

    // Reallocation happened: copy old data to new buffer
    if (elementCount > 0) {
        ptrdiff_t offset = (char*)oldBuffer - (char*)newBuffer;  // constant offset to old data
        char* dst = (char*)newBuffer;
        int i = 0;
        do {
            // Copy one element from old location
            memcpy(dst, dst + offset, elementSize);
            i++;
            dst += elementSize;
        } while (i < elementCount);
    }

    // Free the old buffer
    gMemoryManager->free(oldBuffer, flags);

    // Output the new capacity for the caller
    outNewCapacity = newCapacity;

    // Return 0? (The decompilation shows return local_8 which is 0, but likely an artifact)
    // In practice, this returns the newBuffer in the success path, but here returns 0.
    // We'll conservatively return nullptr to indicate reallocation occurred.
    return nullptr;
}