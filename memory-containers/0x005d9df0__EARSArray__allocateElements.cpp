// FUNC_NAME: EARSArray::allocateElements

// Reconstructed C++ for function at 0x005d9df0 (EARSArray::allocateElements)
// This function allocates a contiguous array of fixed-size elements (0x28 bytes each).
//
// Class layout (presumed):
// +0x00: void** vtable
// +0x04: Allocator* allocator (optional, can be null for default)
// +0x08: void* startPtr     (pointer to allocated memory)
// +0x0C: void* currentPtr   (write cursor, initially same as start)
// +0x10: void* endPtr       (one past the last valid element)

class EARSArray {
public:
    // Allocate space for 'count' elements, each 0x28 bytes.
    // Returns 1 on success, calls error handler if count is too large.
    int __thiscall allocateElements(uint count)
    {
        // Sanity check: maximum count allowed is 0x6666666.
        if (count > 0x6666666) {
            // Error handler (likely logs and returns failure, but here returns 1)
            // FUN_005d9ed0();  // placeholder for error handling
            return 1;
        }

        // Allocator details: if user-provided allocator is null, use a default stack-based temporary.
        Allocator* allocator = this->allocator;
        Allocator defaultAllocator;  // local structure (stack-based, zeroed)
        if (allocator == nullptr) {
            allocator = &defaultAllocator;
        }

        // Call the virtual allocate function (first vtable entry).
        // The allocator's allocate method takes size and returns a pointer.
        void* mem = allocator->allocate(count * 0x28);

        // Set up the internal pointers.
        this->startPtr = mem;
        this->currentPtr = mem;      // write cursor at beginning
        this->endPtr = static_cast<byte*>(mem) + count * 0x28;

        return 1;
    }

private:
    void** vtable;          // +0x00
    Allocator* allocator;   // +0x04
    void* startPtr;         // +0x08
    void* currentPtr;       // +0x0C
    void* endPtr;           // +0x10
};

// Allocator base class (used by EARSArray)
class Allocator {
public:
    virtual void* allocate(size_t size) = 0;  // first vtable entry (index 0)
};