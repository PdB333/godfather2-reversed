// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004cfb00
// Role: Constructor for base EARS object. Sets vtable pointer, calls base initialization,
//       then optionally handles memory management based on flags (bit 0 = free this).

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte flags)
{
    // Set vtable pointer to the class's virtual function table (0x00e36cb4)
    this->vtable = &EARSObject_vtable;  // +0x00

    // Call base class or additional initialization (likely core engine object init)
    initBase();  // FUN_004cfcc0

    // Handle a member at offset 0x04 (probably a pointer to internal data)
    // This may free or release something (e.g., if not null, free it)
    safeRelease(this->memberPtr);  // FUN_009c8eb0(param_1[1])

    // If the lowest bit of flags is set, free the entire object (placement new / custom allocator)
    if ((flags & 1) != 0) {
        safeRelease(this);  // FUN_009c8eb0(param_1)
    }

    return this;
}