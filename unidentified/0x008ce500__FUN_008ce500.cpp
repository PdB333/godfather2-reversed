// FUNC_NAME: SomeClass::constructor
// Function at 0x008ce500
// Constructor for a class with size 0x7C bytes.
// Sets primary vtable at offset 0, secondary vtables at offsets 0x3C and 0x48.
// Initializes a subobject at offset 0x14 via two constructor calls.
// If param_2 bit 0 is set, calls a memory management function (possibly registration or cleanup).

SomeClass* __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Set vtable pointer at +0x00
    this->vtable = (void*)&PTR_FUN_00d7cae8;

    // Set secondary vtable pointers
    this->field_0x3C = (void*)&PTR_LAB_00d7cad8;   // +0x3C
    this->field_0x48 = (void*)&PTR_LAB_00d7cad4;   // +0x48

    // Construct subobject at offset 0x14
    SubObjectType* subObj = reinterpret_cast<SubObjectType*>(&this[0x14]);
    FUN_004086d0(subObj);
    FUN_00408310(subObj);

    // Global initialization routine
    FUN_0046c640();

    // If heap-allocated flag is set, perform additional handling
    if ((flags & 1) != 0)
    {
        // Likely deallocation or registration with memory manager
        FUN_0043b960(this, 0x7C);
    }

    return this;
}