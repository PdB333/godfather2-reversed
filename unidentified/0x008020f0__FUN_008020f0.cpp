// FUNC_NAME: SomeClass::constructor
// This function appears to be a constructor for a class with a vtable at offset +8.
// It first initializes a subobject at offset 0x10, then calls the first virtual function via the vtable.
void __thiscall SomeClass::constructor(void) {
    // Initialize subobject at this+0x10 (likely a base class or member)
    FUN_0070b6a0(reinterpret_cast<uint8_t*>(this) + 0x10);

    // Retrieve vtable pointer from this+8 and call the first virtual function
    typedef void (__thiscall *VirtualFunc)(void*);
    VirtualFunc* vtable = *reinterpret_cast<VirtualFunc**>(reinterpret_cast<uint8_t*>(this) + 8);
    vtable[0](this);
}