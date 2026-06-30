// FUNC_NAME: referenceCountIncrement
// Address: 0x004f7ba0
// Role: Increments a reference count stored in thread-local storage (TLS) at offset 0x30 + index
// Uses FS segment to access the TLS pointer (Windows TIB), then dereferences TLS[8] to get a base pointer.
// Returns the address of the incremented count (or 0 if index is 0).

int referenceCountIncrement(int index)
{
    int* tlsBase;        // TLS pointer from FS:[0x2C]
    int* basePtr;        // Derived from TLS[8]
    int* countAddr;      // Address of reference count

    if (index != 0)
    {
        // Fetch the thread-local storage pointer (TLS array) from FS segment offset 0x2C
        tlsBase = *(int**)__readfsdword(0x2C);

        // Dereference TLS[8] to get the base address of the reference count array
        basePtr = (int*)(*(int*)((char*)tlsBase + 8));

        // Calculate the address of the specific reference count: base + 0x30 + index
        countAddr = (int*)((char*)basePtr + 0x30 + index);

        // Atomically increment the reference count (no lock prefix in the original, so not thread-safe)
        (*countAddr)++;

        // Return the address of the incremented value (used for chaining or verification)
        return (int)((char*)basePtr + 0x30 + index);
    }
    // For index 0, return 0 (invalid/null)
    return 0;
}