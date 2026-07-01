// FUNC_NAME: EARSObject::Constructor
void __fastcall EARSObject::Constructor(EARSObject* this)
{
    // Set vtable pointer (base class vtable at +0x00)
    this->vtable = &PTR_FUN_00d73868;
    // Call base constructor
    FUN_0082b7a0();
    // Set secondary vtable pointer at offset 0x30 (48 bytes)
    this->field_0x30 = &PTR_LAB_00e32854;
    // Call secondary initialization
    FUN_00821f60();
    return;
}