// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(EARSObject *this) {
    // Set vtable pointer (offset +0x0)
    this->vtable = &PTR_FUN_00e32e48;
    // Set function pointers at +0x3C and +0x48
    this->field_0x3C = &PTR_LAB_00e32e64;
    this->field_0x48 = &PTR_LAB_00e32e74;
    // Initialize sub-object at offset +0x50 (size? calls two init functions)
    EARSSubObject::constructor(&this->subObject); // FUN_004086d0
    EARSSubObject::init(&this->subObject);        // FUN_00408310
    // Global initialization step
    EARSGlobal::init();                           // FUN_0046c640
}