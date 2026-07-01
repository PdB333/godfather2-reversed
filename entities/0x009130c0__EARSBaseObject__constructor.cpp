// FUNC_NAME: EARSBaseObject::constructor
void __thiscall EARSBaseObject::constructor(EARSBaseObject* this) {
    // Set vtable pointers for multiple inheritance
    // +0x00: primary vtable pointer
    *this = &PTR_FUN_00d84558;
    // +0x10: secondary vtable pointer (offset 4)
    this[4] = &PTR_LAB_00d84530;
    // +0x50: tertiary vtable pointer (offset 0x14)
    this[0x14] = &PTR_LAB_00d8452c;
    // Overwritten? Possibly intentional for another interface
    this[0x14] = &PTR_LAB_00d84528;

    // Zero global initialization flag
    DAT_01130018 = 0;

    // Call derived/subsystem initializer
    FUN_00957d90();
}