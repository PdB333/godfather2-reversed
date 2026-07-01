// FUNC_NAME: BaseObject::constructor
// Address: 0x00957ed0
// Role: Base class constructor for EARS engine objects. Initializes vtable, secondary pointer, and a flag.

void __thiscall BaseObject::constructor(BaseObject* this) {
    // Call base class initializer (likely another constructor or memory setup)
    FUN_005bf9b0();

    // Set vtable pointer at offset 0x00
    this->vtable = (void**)&PTR_FUN_00d8c370; // +0x00: primary vtable

    // Set secondary pointer at offset 0x10 (param_1[4])
    this->secondaryPtr = (void*)&PTR_LAB_00d8c34c; // +0x10: secondary data/vtable

    // Clear a byte flag at offset 0x13
    *(uint8*)((uint8*)this + 0x13) = 0; // +0x13: flag (e.g., initialized, active)
}