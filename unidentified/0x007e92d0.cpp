// FUN_007e92d0: EARSObject::EARSObject (constructor with initialization flags)
undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte initFlags)
{
    // Base class or common initialization (likely sets up vtable, etc.)
    this->commonInit(); // FUN_007e8f30

    // If flag's bit 0 is set, perform additional setup (e.g., allocate sub‑objects)
    if ((initFlags & 1) != 0) {
        this->additionalInit(); // FUN_009c8eb0
    }

    return this;
}