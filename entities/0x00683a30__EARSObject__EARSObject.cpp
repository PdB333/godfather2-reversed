// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00683a30
// Role: Constructor for EARSObject, sets vtable, calls base constructor, and optionally calls a cleanup/init function based on flag.

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte flags) {
    // Set vtable pointer to EARSObject's vtable (0x00d587e0)
    this->vtable = (void**)&EARSObject_vtable;
    // Call base class constructor (likely EARS::Framework::Object or similar)
    // FUN_004083d0
    BaseClass::BaseClass();
    // If the lowest bit of flags is set, perform additional initialization/cleanup
    // FUN_009c8eb0
    if (flags & 1) {
        this->someMethod();
    }
    return this;
}