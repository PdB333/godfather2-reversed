// FUNC_NAME: UnknownClass::constructor
undefined4* __thiscall UnknownClass::constructor(UnknownClass* this, byte allocFlag)
{
    // Set vtable pointer
    *this = &PTR_FUN_00d81bd0;
    // Set additional internal function tables at offsets +0x3C (0xf*4) and +0x48 (0x12*4)
    this->field_3C = &PTR_LAB_00d81bc0;  // +0x3C
    this->field_48 = &PTR_LAB_00d81bbc;  // +0x48

    // Initialize subobject at offset +0x50 (0x14*4)
    FUN_004086d0(&this->field_50);          // sub_4086d0 (probably some initializer)
    // Initialize subobject at offset +0x58 (0x16*4)
    FUN_00408310(&this->field_58);          // sub_408310 (likely list/array constructor)
    // Initialize subobject at offset +0x60 (0x18*4)
    FUN_00408310(&this->field_60);          // sub_408310
    // Initialize subobject at offset +0x60 (0x18*4) again? Actually no, third call is +0x18*4 = +0x60
    FUN_00408310(&this->field_60);          // sub_408310 (third call, same offset? Possibly a mistake or array of 3?)

    // Global initialization
    FUN_0046c640();                         // sub_46c640 (global singleton?)

    // If allocFlag's bit 0 is set, delete this object (constructor failure cleanup)
    if ((allocFlag & 1) != 0) {
        FUN_0043b960(this, 0x78);           // operator delete (size 0x78)
    }

    return this;
}