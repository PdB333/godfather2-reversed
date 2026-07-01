// FUNC_NAME: EARSObject::EARSObject
undefined4* __thiscall EARSObject::EARSObject(undefined4* this, byte flags)
{
    // Set initial vtable pointers (base class)
    *this = &PTR_FUN_00d777c8;          // +0x00: vtable pointer (base)
    this[1] = &PTR_LAB_00d777b8;        // +0x04: secondary vtable or type info

    // Debug/log call with magic constant (likely allocation tracking)
    FUN_004639e0(0x57600d39);

    // Release any previously held resource at offset +0x08
    if (this[2] != 0) {
        FUN_009c8f10(this[2]);          // +0x08: pointer to resource (e.g., string, sub-object)
    }

    // Override vtable pointers for derived class
    this[1] = &PTR_LAB_00e30fe0;        // +0x04: updated secondary vtable
    *this = &PTR_LAB_00d777b4;          // +0x00: updated main vtable (derived)

    // Global flag reset (e.g., singleton initialization state)
    DAT_011299c0 = 0;

    // If flags bit 0 set, call destructor/cleanup (placement delete?)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}