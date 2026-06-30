// FUNC_NAME: ManagedObject::ManagedObject
// Function address: 0x0055d650
// Role: Constructor for an object that uses TLS-based allocation/deallocation

class ManagedObject {
public:
    void* vtable; // +0x00: pointer to virtual function table
    // Unknown fields: at offset +0x04 (2-byte ushort) likely stores object size or type ID

    ManagedObject(byte allocFlag) __thiscall;
};

ManagedObject::ManagedObject(byte allocFlag) {
    // Set vtable pointer for this class
    this->vtable = (void*)0x00e3a3e4; // VTABLE for ManagedObject

    // Call base class initializer (likely common initialization routine)
    FUN_00bf0c90(); // could be BaseClass::BaseClass()

    // If the object was dynamically allocated (bit 0 of allocFlag set),
    // register it with the TLS-based memory manager for automatic cleanup on exception.
    if ((allocFlag & 1) != 0) {
        // Retrieve thread-local storage value (context for the current thread's allocator)
        void* tlsContext = TlsGetValue(0x01139810); // TLS index from global

        // Call the deallocation registration function
        // Parameters:
        //   - this pointer
        //   - a 2-byte value at offset +0x04 (likely object size or type tag)
        //   - constant 0x0b (11) – possible flag indicating cleanup type
        FUN_00aa26e0(this, *(uint16*)((uint8*)this + 4), 0x0b);
    }
}