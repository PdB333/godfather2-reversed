// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x004e6960
// Purpose: Constructor for a base game object with optional subsystem initialization.
// __thiscall: this passed in ECX, returns this pointer for chaining.
// Parameter initFlag: bit 0 controls whether FUN_009c8eb0 (subsystem init) is called.

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte initFlag) {
    // Call base/parent constructor or common initialization routine.
    // FUN_004e6120 is likely the base class constructor (e.g., ObjectBase::ObjectBase).
    FUN_004e6120();

    // If the lower bit of initFlag is set, perform additional initialization.
    // This pattern is typical for derived classes that need a separate init step.
    if ((initFlag & 1) != 0) {
        // Subsystem initialization, probably setting up virtual tables, fields, etc.
        // +0x00: vtable pointer, +0x04: refcount, etc.
        FUN_009c8eb0(this);
    }
    return this;
}