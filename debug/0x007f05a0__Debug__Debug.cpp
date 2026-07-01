// FUNC_NAME: Debug::Debug
// Address: 0x007f05a0
// Role: Constructor for Debug class. Initializes base object, vtable, and zeroes out internal state.
// Fields documented with offsets relative to this.

__thiscall Debug::Debug(Debug* this, int baseInitParam) {
    // Call base class constructor (likely DebugBase)
    FUN_0046c590(baseInitParam);

    // Set vtable pointer for Debug class
    this->vtable = (DebugVTable*)&PTR_FUN_00d700ac; // +0x00

    // Initialize function table pointers for derived interfaces
    this->table1 = (void*)&PTR_LAB_00d7009c; // +0x3C
    this->table2 = (void*)&PTR_LAB_00d70098; // +0x48

    // Zero out runtime state fields
    this->m_unk50 = 0;     // +0x50 (int)
    this->m_unk54 = 0;     // +0x54 (int)
    this->m_unk58 = 0;     // +0x58 (int)
    this->m_unk5C = 0;     // +0x5C (int)
    this->m_unk60 = 0;     // +0x60 (int)

    // Zero short-sized fields
    this->m_short64 = 0;   // +0x64 (short)
    this->m_short66 = 0;   // +0x66 (short)

    return this;
}