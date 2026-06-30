// FUNC_NAME: EARSObject::Constructor
// Constructor for base object, initializes four int fields to zero and allocates an internal buffer.
void __thiscall EARSObject::Constructor(EARSObject* this)
{
    // +0x00: field_0
    this->field_0 = 0;
    // +0x0C: field_3
    this->field_3 = 0;
    // Allocate 0x14 (20) bytes for internal use; pointer not assigned here.
    FUN_00721c30(0x14, 1);
    // +0x08: field_2
    this->field_2 = 0;
    // +0x04: field_1
    this->field_1 = 0;
    // return this; (implicit in __thiscall)
}