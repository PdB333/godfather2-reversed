//FUNC_NAME: BaseClass::BaseClass
void __thiscall BaseClass::BaseClass(int param) // param_2 stored at +0xC and +0x10
{
    this->field_0xC = param;          // +0x0C: store parameter
    this->field_0x8 = 0;              // +0x08: zero
    this->field_0x4 = 0x21;           // +0x04: set to 33 (max size/type?)
    this->vtable = (void**)0x00d69ad4; // +0x00: vtable pointer
    this->field_0x14 = 0;             // +0x14: zero
    this->field_0x18 = 0;             // +0x18: zero
    this->field_0x1C = 0;             // +0x1C: zero
    this->field_0x20_byte = 0;        // +0x20: byte flag
    this->field_0x10 = this->field_0xC; // +0x10: copy of parameter
    this->field_0x20_byte = 0;        // redundant clear
}