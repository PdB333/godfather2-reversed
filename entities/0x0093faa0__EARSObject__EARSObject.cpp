// FUNC_NAME: EARSObject::EARSObject
void* __thiscall EARSObject::EARSObject(byte flags) {
    // Call base initialization (common for all EARS objects)
    this->baseInit();

    // If the lowest bit is set, perform additional initialization for derived classes
    if (flags & 1) {
        this->derivedInit(this);
    }

    return this;
}