// FUNC_NAME: EARSObject::reset
// Function address: 0x006a8b90
// Role: Reinitialize an EARS engine object. Always calls Destroy first, then if the flag's
//       low bit is set, calls Construct again. Returns the (this) pointer.
//       Typically used to reset an object to a clean state, optionally recreating it.

EARSObject * __thiscall EARSObject::reset(byte flag) {
    this->destroy();   // Calls internal destructor/cleanup (0x006a8530)
    if (flag & 1) {
        this->construct();   // Calls internal constructor/reinit (0x009c8eb0)
    }
    return this;
}