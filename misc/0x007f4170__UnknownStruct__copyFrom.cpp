// FUNC_NAME: UnknownStruct::copyFrom
// Function at 0x007f4170: Copies 13 dwords from source to destination (52 bytes)
// Likely a copy assignment/initialization for a 13-dword structure
void __thiscall UnknownStruct::copyFrom(const UnknownStruct& other) {
    this->field_0x00 = other.field_0x00;
    this->field_0x04 = other.field_0x04;
    this->field_0x08 = other.field_0x08;
    this->field_0x0C = other.field_0x0C;
    this->field_0x10 = other.field_0x10;
    this->field_0x14 = other.field_0x14;
    this->field_0x18 = other.field_0x18;
    this->field_0x1C = other.field_0x1C;
    this->field_0x20 = other.field_0x20;
    this->field_0x24 = other.field_0x24;
    this->field_0x28 = other.field_0x28;
    this->field_0x2C = other.field_0x2C;
    this->field_0x30 = other.field_0x30;
}