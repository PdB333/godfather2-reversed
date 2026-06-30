// FUNC_NAME: BaseClass::constructor
// Function at 0x598db0: Sets the vtable pointer for a base class.
void __fastcall BaseClass::constructor(BaseClass* this) {
    // Set vtable to the class's vtable (at 0x00e3b030)
    this->vtable = (BaseClassVTable*)0x00e3b030;
}