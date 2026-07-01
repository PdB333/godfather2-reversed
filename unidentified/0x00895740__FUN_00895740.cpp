// FUNC_NAME: UnknownClass::constructor_0x895740
void __thiscall UnknownClass::constructor_0x895740(UnknownClass *this)
{
    // Set vtable pointers for class hierarchy
    this->vtable0 = &PTR_FUN_00d77984;                        // +0x00: primary vtable
    this->field_0x3C = &PTR_LAB_00d77974;                     // +0x3C: secondary vtable (offset 0xF)
    this->field_0x48 = &PTR_LAB_00d77970;                     // +0x48: tertiary vtable (offset 0x12)
    this->subObject = &PTR_LAB_00d77968;                      // +0x50: sub-object vtable at offset 0x14

    // Initialize sub-object at +0x50 with parameter from +0x54
    FUN_00894800(&this->subObject, this->field_0x54);         // constructor for sub-object

    // Initialize two small sub-objects (e.g., lists or arrays) at +0x5C and +0x64
    FUN_004086d0(&this->field_0x5C);                          // init call 1
    FUN_004086d0(&this->field_0x64);                          // init call 2

    // Clear/reset those sub-objects and a third at +0x6C
    FUN_00408310(&this->field_0x5C);                          // clear/reset 1
    FUN_00408310(&this->field_0x64);                          // clear/reset 2
    FUN_00408310(&this->field_0x6C);                          // clear/reset 3

    // Override sub-object vtable with purecall vtable (makes it abstract)
    this->subObject = &PTR___purecall_00d77960;               // +0x50 now pure virtual

    // Additional global initialization
    FUN_0046c640();                                           // e.g., register with manager
}