// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(EARSObject *this) {
    // Set vtable pointer to derived class (offset +0x0)
    *this = &g_vtable_Derived;
    // Call base class constructor on the base subobject at offset +0xC
    baseClassConstructor(this[3]);  // this[3] is offset 0xC
    // Set vtable pointer to base class (final)
    *this = &g_vtable_Base;
    return;
}