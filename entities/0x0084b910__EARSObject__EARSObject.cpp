// FUNC_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(EARSObject *this)
{
    // Set vtable pointer (at +0x00)
    this->vtable = &PTR_FUN_00d74dbc; // +0x00
    // Initialize fields to zero (offsets relative to this)
    // Note: The original assembly initializes in a non-sequential order:
    // +0x04, +0x08, then +0x18, +0x1C, +0x20, then +0x14, +0x10, +0x0C.
    // For clarity, we list them in offset order.
    this->field_04 = 0; // +0x04
    this->field_08 = 0; // +0x08
    this->field_0C = 0; // +0x0C
    this->field_10 = 0; // +0x10
    this->field_14 = 0; // +0x14
    this->field_18 = 0; // +0x18
    this->field_1C = 0; // +0x1C
    this->field_20 = 0; // +0x20
    return;
}