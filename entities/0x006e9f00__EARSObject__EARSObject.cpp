// FUNC_NAME: EARSObject::EARSObject
void* __thiscall EARSObject::EARSObject(void* this, byte flags) {
    // Call base class constructor (implicit this)
    baseConstructor();

    // If the flag bit 0 is set, perform additional initialization
    if (flags & 1) {
        additionalInit(this);
    }

    return this;
}