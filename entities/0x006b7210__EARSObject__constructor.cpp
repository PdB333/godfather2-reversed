// FUNC_NAME: EARSObject::constructor
// Address: 0x006b7210
// Role: Constructor for EARSObject (size 0x2a0). Calls base constructor and optionally deallocates memory if allocFlag has bit 0 set.

EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte allocFlag) {
    this->baseConstructor();           // FUN_006b7030 - base class initialization
    if (allocFlag & 1) {
        operator delete(this, 0x2a0);  // FUN_0043b960 - deallocate with object size
    }
    return this;
}