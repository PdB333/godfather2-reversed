// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte param_2) {
    // Call base class initialization or common init routine
    EARSObject::commonInit(); // FUN_004f4d50

    // If bit 0 of flags is set, perform deallocation or cleanup
    // This is unusual for a constructor; possibly a placement new that
    // conditionally destroys the object if the memory is invalid or pre-used.
    if ((param_2 & 1) != 0) {
        EARSObject::release(this); // FUN_009c8eb0 - likely destructor or memory deallocation
    }

    return this;
}