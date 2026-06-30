// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(void) {
    // +0x00: vtable pointer
    this->vtable = &PTR_FUN_00d61de8;
    // +0x04..0x18: six fields (all set to 0)
    this->field_04 = 0;
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    // +0x1C..0x34: seven fields (set to global default)
    undefined4 defaultConstant = DAT_00d5ccf8; // global default value (likely 1.0f or 0.0f)
    this->field_1C = defaultConstant;
    this->field_20 = defaultConstant;
    this->field_24 = defaultConstant;
    this->field_28 = defaultConstant;
    this->field_2C = defaultConstant;
    this->field_30 = defaultConstant;
    this->field_34 = defaultConstant;
    // +0x38: int zero
    this->field_38 = 0;
    // +0x3C: short zero
    *(short*)(&this->field_3A) = 0; // writing 2 bytes at offset 0x3C (field_3A is placeholder)
    // note: the exact field at +0x3C is a short, but we write it as such
}