// FUNC_NAME: SomeStruct::init
void __fastcall SomeStruct::init(SomeStruct* this)
{
    // Initialize most fields to zero; field at offset 0x10 (index 4) is left unchanged.
    this->field_0 = 0;    // +0x00
    this->field_4 = 0;    // +0x04
    this->field_8 = 0;    // +0x08
    this->field_C = 0;    // +0x0C
    // field_10 (index 4) is not zeroed – possibly a pointer or flag set elsewhere
    this->field_14 = 0;   // +0x14
    this->field_18 = 0;   // +0x18
    this->field_1C = 0;   // +0x1C
    this->field_20 = 0;   // +0x20
    this->field_24 = 0;   // +0x24
    this->field_28 = 0;   // +0x28
    this->field_2C = 0;   // +0x2C
}