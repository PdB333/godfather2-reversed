// FUNC_NAME: EARS::Framework::SmallPooledObject::constructor
int __thiscall SmallPooledObject::constructor(SmallPooledObject* this, byte flags) {
    // Call base constructor (likely initializes vtable pointer and basic members)
    SmallPooledObject::baseConstructor();

    // If the low bit of flags is set, deallocate this object from thread-local pool
    if ((flags & 1) != 0) {
        // Retrieve the per-thread memory manager from TLS
        void* tlsManager = TlsGetValue(gTLSMemoryManagerIndex);
        // Deallocate this object: size stored at offset +4 (uint16), type ID 0xB
        MemoryManager_Deallocate(this, *(uint16_t*)((uint8_t*)this + 4), 0xB);
    }

    return (int)this;
}