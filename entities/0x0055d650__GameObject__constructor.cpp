// FUNC_NAME: GameObject::constructor
undefined4* __thiscall GameObject::constructor(undefined4* thisPtr, byte flags)
{
    // Set vtable pointer to class-specific vtable
    *thisPtr = &PTR_FUN_00e3a3e4;

    // Call base class constructor
    baseClass::constructor();

    // If the object was heap-allocated (flags bit 0 set), 
    // perform thread-local storage cleanup or deallocation
    if ((flags & 1) != 0) {
        // Retrieve thread-local storage value (likely allocator context)
        void* tlsValue = TlsGetValue(DAT_01139810);
        // Call deallocation function with size from offset +0x04 and allocation type 0xb
        freeObject(thisPtr, *(uint16_t*)(thisPtr + 1), 0xb);
    }

    return thisPtr;
}