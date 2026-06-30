// FUNC_NAME: MemoryPoolObject::constructor
int __thiscall MemoryPoolObject::constructor(int thisPtr, byte flags)
{
    // Call base class constructor (likely initializes vtable and other members)
    MemoryPoolObject::baseConstructor();

    // Check flag bit 0: indicates whether to use thread-local storage (TLS) pool
    if ((flags & 1) != 0) {
        // Retrieve thread-local storage value associated with gTlsHeapIndex
        // (this likely returns a pointer to the current thread's memory heap manager)
        TlsGetValue(gTlsHeapIndex); // Result not directly used; may have side effects or be implicit

        // Record allocation info: this object was allocated from a TLS pool.
        // The size (stored at thisPtr+4) and pool ID (0x2f = 47) are passed.
        // FUN_00aa26e0 is probably a TLS heap method (e.g., TlsHeap::registerObject).
        TlsHeap::registerAllocation(thisPtr, *(unsigned short *)(thisPtr + 4), 0x2f);
    }

    return thisPtr;
}