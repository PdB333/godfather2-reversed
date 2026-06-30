// FUNC_NAME: EARSObject::constructor

// Constructor for an EARS object. Performs base initialization and conditionally
// calls an additional setup routine (e.g., for derived classes or placement new).
// @param this: pointer to uninitialized memory
// @param flags: if bit 0 is set, also calls onConstructionCompleted
EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte flags)
{
    // Base class initialization (likely sets vtable pointer or member defaults)
    BaseObject::init(this); // FUN_00b0fa90

    // If the low bit is set, perform additional construction steps
    // (e.g., allocate resources, register with manager)
    if ((flags & 1) != 0) {
        this->onConstructionCompleted(); // FUN_009c8eb0
    }

    return this;
}