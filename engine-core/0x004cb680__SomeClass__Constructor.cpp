// FUNC_NAME: SomeClass::Constructor
// Address: 0x004cb680
// Role: Constructor for SomeClass (sets vtable, calls base constructor, handles allocation flag)

void* __thiscall SomeClass::Constructor(byte allocFlag)
{
    // Set vtable pointer (offset +0x00) to class vtable table
    this->vtable = &SomeClass_vtable;   // PTR_LAB_00e36658

    // Call base class constructor (likely BaseClass::Constructor)
    FUN_00654d40();

    // If the allocation flag indicates heap-allocated object, call cleanup function
    // (FUN_009c8eb0 probably performs operator delete or destructor)
    if (allocFlag & 1) {
        FUN_009c8eb0(this);
    }

    return this;
}