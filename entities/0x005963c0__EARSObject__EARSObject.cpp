// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x005963c0
// Role: Constructor for base EARS object, initializes vtable and a flag.
void __fastcall EARSObject::EARSObject(EARSObject* this) {
    // Set vtable pointer (offset +0x0)
    this->vtable = &PTR_FUN_00e3adf0;
    // Initialize byte at offset +0x4 to false (likely a boolean flag)
    this->someFlag = false;
}