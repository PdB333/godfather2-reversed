// FUNC_NAME: EARSObject::EARSObject
// Constructor for a base EARS object. Sets up vtable and function pointer tables, zeros some fields, then calls a class-specific initializer.
void __thiscall EARSObject::EARSObject()
{
    // Call base class constructor (likely Object::Object or SimObject::SimObject)
    FUN_004737b0();

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d5f678;            // +0x00: vtable

    // Set function pointer tables (possibly for interface dispatch)
    this->funcTable1 = &PTR_LAB_00d5f668;        // +0x3C (offset 0xf)
    this->funcTable2 = &PTR_LAB_00d5f664;        // +0x48 (offset 0x12)
    this->funcTable3 = &PTR_LAB_00d5f660;        // +0x50 (offset 0x14)

    // Zero out four consecutive words (likely next/prev pointers or status flags)
    this->field_0x58 = 0;                        // +0x58
    this->field_0x5C = 0;                        // +0x5C
    this->field_0x60 = 0;                        // +0x60
    this->field_0x64 = 0;                        // +0x64

    // Additional initialization specific to this derived class
    FUN_006dc940();
}