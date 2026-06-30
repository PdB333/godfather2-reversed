// FUNC_NAME: EARS::Framework::Object::Object
// Address: 0x00540310
// Role: Constructor for EARS::Framework::Object, with optional TLS registration

// Known: TLS index stored at DAT_01139810, used for thread-local object tracking
// Known: FUN_00aa26e0 registers object in TLS with vtable pointer and size code 0x27 (39 bytes)

int __thiscall EARSObjectConstructor(void* this_ptr, byte flags)
{
    // Call base class constructor (likely EARS::Foundation::Object or similar)
    BaseClassConstructor();

    // If bit 0 of flags is set, perform TLS registration
    if ((flags & 1) != 0)
    {
        // Retrieve thread-local storage pointer using global TLS index
        void* tlsData = TlsGetValue(g_tlsIndex); // g_tlsIndex = DAT_01139810

        // Register this object in TLS: pass this, vtable pointer (at +0x04), and size constant 0x27
        // FUN_00aa26e0 likely adds object to a linked list or pool in this thread's storage
        RegisterObjectInTLS(this_ptr, *(unsigned short*)((char*)this_ptr + 4), 0x27);
    }

    return this_ptr; // return this pointer for chaining
}