// FUNC_NAME: UnknownClass::~UnknownClass (scalar deleting destructor, offset 0x6ccf90)
undefined4* __thiscall UnknownClass::~UnknownClass(undefined4* this, byte param_2)
{
    // Set vtable to the most derived class for virtual dispatch during destruction
    *this = &PTR_FUN_00d5f134;

    // Set vtable pointers for sub-objects at offsets 0x3C, 0x48, 0x50
    this[0xf] = &PTR_LAB_00d5f124;  // +0x3C base/secondary vtable
    this[0x12] = &PTR_LAB_00d5f120; // +0x48
    this[0x14] = &PTR_LAB_00d5f11c; // +0x50

    // Release sub-object pointers if non-null
    if (this[0x20] != 0) {          // +0x80
        FUN_004daf90(this + 0x20);  // release sub-object (e.g., container, allocated block)
    }
    if (this[0x1e] != 0) {          // +0x78
        FUN_004daf90(this + 0x1e);  // release another sub-object
    }

    // Call base class destructor
    FUN_00473880();                 // ~BaseClass()

    // Conditionally free the object's memory (scalar deleting)
    if ((param_2 & 1) != 0) {
        FUN_0043b960(this, 0x98);   // operator delete(this, sizeof(UnknownClass))
    }

    return this;
}