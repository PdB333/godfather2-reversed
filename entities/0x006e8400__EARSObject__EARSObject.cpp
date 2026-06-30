// FUNC_NAME: EARSObject::EARSObject
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte flags) {
    // Call base class constructor / initializer
    this->baseConstructor(); // FUN_006e79c0

    // If the flags indicate that this object was dynamically allocated (bit 0 set),
    // call operator delete to free memory (e.g., on construction failure or cleanup).
    if (flags & 1) {
        EARSObject::operatorDelete(this); // FUN_009c8eb0
    }

    return this;
}