// FUNC_NAME: EARSObject::EARSObject (constructor at 0x00684120)
// Role: Initializes an EARS engine base object with dual vtable pointer assignment.
// Sets up two vtables (primary at offset 0x0, secondary at offset 0x3C, tertiary at offset 0x48) 
// and calls base then derived initialization functions.

void __fastcall EARSObject::EARSObject(EARSObject *this)
{
    // Set base vtable (first interface)
    this->vtable = &PTR_FUN_00d588bc;           // +0x00
    this->field_0x3C = &PTR_LAB_00d588ac;       // +0x3C (likely second vtable/interface)
    this->field_0x48 = &PTR_LAB_00d588a8;       // +0x48 (third vtable/interface)
    FUN_0078ecf0();                              // base class initialization
    // Overwrite with derived vtables
    this->vtable = &PTR_FUN_00d5888c;           // +0x00
    this->field_0x3C = &PTR_LAB_00d5887c;       // +0x3C
    this->field_0x48 = &PTR_LAB_00d58878;       // +0x48
    FUN_0046c640();                              // derived class initialization
    return;
}