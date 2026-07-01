// FUNC_NAME: BaseObject::BaseObject
void __fastcall BaseObject::BaseObject(BaseObject *this)
{
    // Clear fields from +0x04 to +0x1C (inclusive)
    this->field_04 = 0;
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;

    // Set debug sentinel values (uninitialized marker)
    this->field_20 = 0xBADBADBA;   // +0x20
    this->field_24 = 0xBEEFBEEF;   // +0x24
    this->field_28 = 0xEAC15A55;   // +0x28

    // Clear other fields
    this->field_30 = 0;            // +0x30
    this->field_34 = 0;            // +0x34
    this->field_38 = 0;            // +0x38
    this->field_2C = 0;            // +0x2C

    // Clear previously set sentinel values (actually zeros the same memory)
    this->field_28 = 0;            // +0x28
    this->field_24 = 0;            // +0x24
    this->field_20 = 0;            // +0x20

    // Set vtable-like pointers
    this->field_3C = &PTR_FUN_00e32808;  // +0x3C
    this->field_40 = 0;            // +0x40
    this->vtable = &PTR_FUN_00d680b4;    // +0x00
    this->field_3C = &PTR_LAB_00d680b0;  // +0x3C (replaced)

    // Zero more fields
    this->field_44 = 0;            // +0x44
    this->field_48 = 0;            // +0x48
    this->field_4C = 0;            // +0x4C

    // Type/category field (value 2)
    this->field_50 = 2;            // +0x50

    // Another set of debug sentinels, then cleared
    this->field_54 = 0xBADBADBA;   // +0x54
    this->field_58 = 0xBEEFBEEF;   // +0x58
    this->field_5C = 0xEAC15A55;   // +0x5C
    this->field_60 = 0;            // +0x60

    // Clear sentinels again
    this->field_5C = 0;            // +0x5C
    this->field_58 = 0;            // +0x58
    this->field_54 = 0;            // +0x54

    return;
}