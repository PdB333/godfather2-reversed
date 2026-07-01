// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(SomeClass *this, uint flag) {
    // Set vtable pointers for multiple base classes (scalar deleting destructor)
    this->vtable0 = &PTR_FUN_00d820d0;       // +0x00
    this->vtable1 = &PTR_LAB_00d820c0;       // +0x3C
    this->vtable2 = &PTR_LAB_00d820bc;       // +0x48
    this->vtable3 = &PTR_LAB_00d820b8;       // +0x50
    this->vtable4 = &PTR_LAB_00d82058;       // +0x54
    this->vtable5 = &PTR_LAB_00d81ff0;       // +0x58
    FUN_009018b0();  // base destructor chain
    if (flag & 1) {
        FUN_0043b960(this, 0x240);  // operator delete(this, 0x240)
    }
    return (undefined4 *)this;
}