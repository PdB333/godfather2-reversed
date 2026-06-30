// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004f7850
// Role: Constructor for a base engine object, initializes vtable pointer and default member values from a global default.

void __thiscall EARSObject::EARSObject(EARSObject *this)
{
    int defaultValue = DAT_00e2b1a4; // Global default value (likely -1 or 0)

    // Set vtable pointer (offset +0x00)
    this->vtable = &PTR_FUN_00e37930;

    // Zero out immediate fields (offset +0x04)
    this->field_04 = 0;

    // Zero out fields at offsets +0x20, +0x24, +0x28
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_28 = 0;

    // Zero out field at offset +0x38
    this->field_38 = 0;

    // Set fields at offsets +0x10 through +0x1c to the default value
    this->field_10 = defaultValue;
    this->field_14 = defaultValue;
    this->field_18 = defaultValue;
    this->field_1c = defaultValue;

    // Set fields at offsets +0x2c, +0x30, +0x34 to the default value
    this->field_2c = defaultValue;
    this->field_30 = defaultValue;
    this->field_34 = defaultValue;
}