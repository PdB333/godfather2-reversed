// FUNC_NAME: BaseType::constructor (object initializer with TLS allocation)
// Address: 0x00563c70
// Role: Initializes an object, optionally allocating from thread-local storage if flag bit 0 is set.
// The function first calls a global initialization routine, then conditionally retrieves a TLS value
// and calls an internal allocation function with a size of 0x2f (47 bytes) and a 16-bit type ID from offset +0x4.

int __thiscall BaseType::constructor(int this, byte flags)
{
    // Global initialization (likely memory manager or singleton)
    GlobalInit::ensureInitialized();

    if ((flags & 1) != 0) {
        // Retrieve thread-local storage pointer (e.g., per-thread memory pool)
        void* tlsValue = TlsGetValue(DAT_01139810);
        // Allocate or initialize an internal structure of size 0x2f using the type ID from offset +0x4
        MemoryManager::allocateFromTLS(this, *(short*)(this + 4), 0x2f);
    }

    return this; // Return the initialized object pointer
}