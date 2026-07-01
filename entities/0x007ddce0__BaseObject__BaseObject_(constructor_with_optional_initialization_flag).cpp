// FUNC_NAME: BaseObject::BaseObject (constructor with optional initialization flag)
// @ 0x007ddce0 - Base class constructor. Calls common initialization (0x007ddae0) unconditionally.
// If param_2 bit 0 is set, also calls additional initialization (0x00624da0) for extended setup.
// Returns the this pointer.

BaseObject* __thiscall BaseObject::BaseObject(BaseObject* this, byte initFlags)
{
    // Perform base initialization (common to all instances)
    this->baseInitialize();      // FUN_007ddae0

    // If bit 0 of initFlags is set, perform extended initialization
    if ((initFlags & 1) != 0)
    {
        this->extendedInitialize(); // FUN_00624da0
    }

    return this;
}