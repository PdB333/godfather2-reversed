// FUNC_NAME: ActionOptions::initialize
void __thiscall ActionOptions::initialize(int param2, uint8_t param3)
{
    // +0x00: action type (always 4 for this variant)
    this->type = 4;
    // +0x04: action subtype (always 4 for this variant)
    this->subtype = 4;
    // +0x08: unique identifier or target
    this->id = param2;
    // +0x0C: flags / subfields, cleared
    this->field_0C = 0;
    // +0x10 through +0x28: cleared (6 ints)
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    // +0x28: int cleared
    this->field_28 = 0;
    // +0x2C: low byte set to parameter parameter
    *(uint8_t*)((uintptr_t)this + 0x2C) = param3;
    // +0x2D..0x2F: byte padding cleared
    *(uint8_t*)((uintptr_t)this + 0x2D) = 0;
    *(uint8_t*)((uintptr_t)this + 0x2E) = 0;
    *(uint8_t*)((uintptr_t)this + 0x2F) = 0;
    // +0x30: additional byte flag cleared
    *(uint8_t*)((uintptr_t)this + 0x30) = 0;
    // +0x34..0x40: remaining data cleared
    this->field_34 = 0;
    this->field_38 = 0;
    this->field_3C = 0;
    this->field_40 = 0;
}