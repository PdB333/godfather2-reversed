// FUNC_NAME: SimBase::constructor

// Address: 0x0064cc90
// Role: Base class constructor for EARS engine objects.
// Sets the vtable pointer and zeroes out state fields at offsets 0x60, 0x64, 0x68, 0x6C.

void __fastcall SimBase::constructor(SimBase* thisPtr)
{
    // Set virtual function table pointer (first member)
    thisPtr->vtable = &PTR_LAB_00e317c4;

    // Zero out internal fields (likely reference count, flags, timers, etc.)
    thisPtr->field_0x60 = 0;  // +0x60
    thisPtr->field_0x64 = 0;  // +0x64
    thisPtr->field_0x68 = 0;  // +0x68
    thisPtr->field_0x6C = 0;  // +0x6C
}