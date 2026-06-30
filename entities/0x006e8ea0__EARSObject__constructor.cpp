// FUNC_NAME: EARSObject::constructor

__thiscall EARSObject* EARSObject::constructor(EARSObject* this, byte flag) {
    // Set virtual function table pointer
    *this = &PTR_FUN_00d5fc10; // +0x00 vtable

    // Call base class initializer (likely EARSObject::init or Object::constructor)
    FUN_004149b0();

    // If bit 0 of flag is set, perform additional cleanup or destruction logic
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}