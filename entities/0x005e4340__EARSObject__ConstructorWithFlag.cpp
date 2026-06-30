// FUNC_NAME: EARSObject::ConstructorWithFlag
// Address: 0x005e4340
// Role: Constructor that optionally calls a cleanup/destroy function based on flag.
// The flag (param_2) bit 0 triggers a call to a deallocation or finalization routine.

undefined4 __thiscall EARSObject::ConstructorWithFlag(byte param_2)
{
    // +0x00: vtable or base data
    this->InternalConstruct(); // 0x005e4360: base initialization
    if ((param_2 & 1) != 0) {
        this->CleanupOrDestroy(); // 0x009c8eb0: optional cleanup (e.g., operator delete)
    }
    return this;
}