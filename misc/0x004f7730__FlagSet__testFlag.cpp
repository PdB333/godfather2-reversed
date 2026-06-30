// FUNC_NAME: FlagSet::testFlag
// Address: 0x004f7730
// Tests if a flag identified by flagId is set in the FlagSet.
// Returns the flagId if set, otherwise 0. Uses a vtable method at offset 0x10.

uint32_t FlagSet::testFlag(uint32_t flagId) {
    // Vtable function signature: char (__thiscall*)(FlagSet*, uint32_t, uint32_t*)
    // The third parameter is an optional output value, ignored here.
    uint32_t ignored;
    typedef char (__thiscall* FlagCheckFunc)(FlagSet*, uint32_t, uint32_t*);
    FlagCheckFunc func = (FlagCheckFunc)(*reinterpret_cast<void***>(this))[4]; // offset 0x10 / 4
    char result = func(this, flagId, &ignored);
    // Branchless: convert bool to mask, mask flagId
    return -(uint32_t)(result != '\0') & flagId;
}