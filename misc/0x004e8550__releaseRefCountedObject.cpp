// FUNC_NAME: releaseRefCountedObject

// This function implements a reference-counted object release pattern.
// It takes a pointer to an object and a pointer to a reference count control block.
// The control block has a virtual table (vtable) with two methods at offsets 4 and 8.
// Offset 4: deleteSelf() - destroys the control block (and possibly the object).
// Offset 8: shouldDelete(void* object) - returns true if the object should be deleted
// (e.g., not shared, or release requested).
// The function decrements the refcount; if it reaches zero, deleteSelf() is called.
// Returns true if the object was released (i.e., shouldDelete returned true),
// false otherwise.

struct RefCountControlBlock
{
    void** vtable; // +0x00: pointer to vtable
    int refCount;  // +0x04: reference count (after vtable pointer)
};

// vtable offsets (relative to vtable base)
// offset 4: void (*deleteSelf)();               // no parameters, called on the block
// offset 8: bool (*shouldDelete)(void* object);  // takes object pointer

bool __fastcall releaseRefCountedObject(void* object, RefCountControlBlock* block)
{
    // Dummy local used as a sentinel; the decompiler showed return of &local_4
    // Interpreted as a non-null pointer for success; we just return bool.
    // local_4 = 0; // not needed in reconstructed code

    if (block != nullptr)
    {
        // Call virtual function at vtable + 8 to determine if release is allowed
        // The call uses the object pointer as the argument (likely the object's this pointer)
        bool bShouldDelete = ((bool (*)(void*))(block->vtable[2]))(object); // offset 8 is index 2 (4 bytes per entry? assuming 4-byte pointers)
        // Actually vtable[1] would be offset 4, vtable[2] offset 8

        // Decrement reference count
        block->refCount--;

        // If reference count reaches zero, call virtual destructor at vtable + 4
        if (block->refCount == 0)
        {
            // Call vtable[1] (offset 4) which is a void(*)(void) - no arguments
            ((void (*)())(block->vtable[1]))();
        }

        // Return whether the release was requested (simplified as bool)
        // Original returned pointer to local_4 (non-null) if true, else null.
        return bShouldDelete;
    }
    return false;
}