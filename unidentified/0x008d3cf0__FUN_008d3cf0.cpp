// FUNC_NAME: UnknownClass::~UnknownClass
void __thiscall UnknownClass::~UnknownClass(UnknownClass *this) {
    // Set vtable to destructor-specific vtable for this class
    this->vtable_main = &PTR_FUN_00d7d55c;
    // For multiple inheritance, also set second vtable pointer
    this->vtable_secondary = &PTR_LAB_00d7d54c;

    // If the resource flag at offset 0x20 is set, release a global buffer
    if (this->resourceFlag != 0) {
        releaseGlobalBuffer(&g_globalBuffer);
        this->resourceFlag = 0;
    }

    // Switch vtables to base class versions before calling base destructors
    this->vtable_main = &PTR_FUN_00d7d4d8;
    this->vtable_secondary = &PTR_LAB_00d7d4c8;

    // Release member arrays at offsets 0x58 and 0x68
    // param_1 + 0x16 -> offset 0x58, param_1 + 0x1a -> offset 0x68 (assuming 4-byte pointer size)
    releaseMemberArray(&(this->memberArray1));
    releaseMemberArray(&(this->memberArray2));

    // Call base class destructors (chained)
    baseDestructor1();
    baseDestructor2();
}