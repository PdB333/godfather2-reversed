// FUNC_NAME: SomeGameObject::constructor
// Function at 0x00563cb0: Constructor with TLS-based cleanup logic (flag param indicates allocated memory)
int __thiscall SomeGameObject::constructor(char flagAllocated)
{
    // Call base class constructor or initializer
    baseConstructor();

    // If the object was heap-allocated (bit 0 set), perform TLS-based cleanup/registration
    if ((flagAllocated & 1) != 0) {
        // Retrieve current thread's storage for allocation tracking (DAT_01139810 is a TLS index)
        void* tlsValue = TlsGetValue(g_tlsIndex);

        // Call a function that likely frees or registers the object with size from offset +4 (e.g., a vtable offset or object size)
        // Third parameter 0x2F (47) may represent a type ID or debug flag
        FUN_00aa26e0(this, *(unsigned short*)((int)this + 4), 0x2F);
    }

    return this;
}