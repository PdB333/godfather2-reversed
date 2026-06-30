// FUNC_NAME: EARSObject::constructor
EARSObject * __thiscall EARSObject::constructor(EARSObject *this, int arg2, int arg3) {
    // Call base class constructor (likely EARSBaseObject or similar)
    EARSBaseObject::constructor((EARSBaseObject *)this, arg2, arg3);

    // Set vtable pointer
    this->vftable = (void *)&PTR_LAB_00d64e80; // vtable for EARSObject

    // Multiple inheritance adjustment:
    // If field at +0x48 is non‑zero, compute a derived pointer by subtracting 0x48 from it.
    // This is typical casting logic for virtual base class offsets.
    int subObjPtr = this->field_0x48;
    if (subObjPtr != 0) {
        this->field_0x50 = subObjPtr - 0x48;
    } else {
        this->field_0x50 = 0;
    }

    // Initialize other fields
    this->field_0x54 = 0;   // +0x54
    this->field_0x58 = 0;   // +0x58
    this->field_0x5C = -1;  // +0x5C
    this->field_0x6C = 0;   // +0x6C (byte)
    this->field_0x68 = 0;   // +0x68
    this->field_0x64 = 0;   // +0x64
    this->field_0x60 = 0;   // +0x60

    return this;
}