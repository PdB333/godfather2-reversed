// FUNC_NAME: EARSObject::Constructor
undefined4* __thiscall EARSObject::Constructor(undefined4* this, byte param_2)
{
    // Set up vtable pointers for multiple inheritance
    *this = &PTR_FUN_00d761a0;            // Primary vtable
    this[0xf] = &PTR_LAB_00d76190;        // Secondary vtable at offset +0x3C
    this[0x12] = &PTR_LAB_00d7618c;       // Tertiary vtable at offset +0x48
    this[0x14] = &PTR_LAB_00d76188;       // Quaternary vtable at offset +0x50

    // Call base class initializer (likely a static initialization routine)
    FUN_007256d0();

    // If object is heap-allocated (param_2 & 1), execute custom memory setup
    if ((param_2 & 1) != 0) {
        FUN_0043b960(this, 0x170); // Possibly a placement new or memory hook for 0x170 bytes
    }

    return this;
}