// FUNC_NAME: ObjectClass::constructor
// Function address: 0x0096db20
// Role: Initializes a game object (likely an EARS GameObject subclass) by setting
//       vtable pointer at +0x00 and a class meta pointer at +0x10.
//       Calls a common initialization routine (FUN_005bf9b0) first.

void* __fastcall ObjectClass::constructor(ObjectClass* this)
{
    // Sub-initialization, possibly base class constructor or common setup
    FUN_005bf9b0();

    // Set vtable pointer (offset +0x00)
    this->vtable = (void*)0x00d8eb70;

    // Set pointer at offset +0x10 (likely a class meta/type info pointer)
    this->field_0x10 = (void*)0x00d8eb48;

    return this;
}