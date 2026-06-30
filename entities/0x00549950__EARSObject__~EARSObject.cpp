// FUNC_NAME: EARSObject::~EARSObject
// Function address: 0x00549950
// Role: Destructor (deleting and non-deleting) for an EARS base object
// Releases a reference-counted shared block (at +0x18) and optionally deallocates memory

undefined4 * __thiscall EARSObject::~EARSObject(undefined4 *this, byte mode)
{
    // +0x18: pointer to a reference-counted block (shared_ptr implementation)
    undefined4 *refBlock = (undefined4 *)this[6];
    
    // Set vtable to the destructor-specific table (likely for virtual destructor chain)
    *this = &PTR_FUN_00e39ba8;
    
    if (refBlock != (undefined4 *)0x0) {
        // refBlock structure:
        // +0: vtable pointer to the managed object's deletion function
        // +4: weak reference count (short)
        // +6: strong reference count (short)
        short weakCount = *(short *)(refBlock + 1);   // offset +4
        if (weakCount != 0) {
            short *strongCount = (short *)((int)refBlock + 6);
            *strongCount = *strongCount - 1;          // decrement strong ref
            if (*strongCount == 0) {
                // Strong refs reached zero -> delete the managed object
                // Call the deletion function via the block's vtable with argument 1
                (**(code **)*refBlock)(1);
            }
        }
        // Clear the shared pointer
        this[6] = 0;
    }
    
    // Restore base class vtable (for further destructor chaining)
    *this = &PTR_LAB_00d96914;
    
    // If mode bit 0 is set (deleting destructor), deallocate this object
    if ((mode & 1) != 0) {
        // Retrieve thread-local storage for the custom allocator
        TlsGetValue(DAT_01139810);  // return value unused, likely for allocator context
        // Deallocate: object pointer, size from this+1 (offset +4, stored as short), type 0xb
        FUN_00aa26e0(this, *(short *)(this + 1), 0xb);
    }
    
    return this;
}