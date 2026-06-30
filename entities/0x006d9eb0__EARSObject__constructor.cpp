// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(EARSObject *this, byte flags) {
    // Call base class constructor
    this->baseConstructor();

    // If the low bit of flags is set, perform cleanup (e.g., deallocation)
    if ((flags & 1) != 0) {
        int *vtable = (int *)getClassVtable();
        // Call virtual destructor or deallocation function at vtable+4 with size 0x80
        (*(code **)(*vtable + 4))(this, 0x80);
    }

    return this;
}