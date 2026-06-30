// FUNC_NAME: EARSBaseObject::constructor
void __thiscall EARSBaseObject::constructor(EARSBaseObject* this) {
    // vtable pointer at offset 0x00
    this->vtable = (void*)0x00e407c8;
    // field at +0x04 (likely some flag or ID) initialized to 0
    this->field_0x04 = 0;
    // field at +0x08 (another integer)
    this->field_0x08 = 0;
    // field at +0x0C (another integer)
    this->field_0x0C = 0;
    // field at +0x10 initialized from global DAT_00e2eff4 (possibly a pointer or constant)
    this->field_0x10 = (int*)DAT_00e2eff4;
}