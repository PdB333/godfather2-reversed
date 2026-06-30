// FUNC_NAME: EARSObject::EARSObject
// Function at 0x00481520 - Constructor: initializes vtable and calls base constructor
void __thiscall EARSObject::EARSObject(EARSObject* this) {
    // Set vtable pointer to this class's vtbl
    this->vtable = (void**)0x00e33520;  // +0x00: vtable pointer
    // Call base class constructor (likely FUN_00454390 is the base EARSObject constructor)
    FUN_00454390(this);
    return;
}