// FUNC_NAME: EARSObject::EARSObject
void* __thiscall EARSObject::EARSObject(byte flags) {
    // Call base constructor / common initialization (0x581a70)
    baseInit();

    // Conditional extra initialization when flag bit 0 is set
    if (flags & 1) {
        conditionalInit(this); // 0x9c8eb0
    }

    return this;
}