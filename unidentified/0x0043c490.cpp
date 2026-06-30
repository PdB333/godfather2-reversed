// FUN_NAME: EntityBase::setBitFlag
void __thiscall EntityBase::setBitFlag(void)
{
    // This function sets a bit in a 64-bit flag field at offsets +0x148 (low) and +0x14c (high).
    // The exact bit index is determined by a helper function (FUN_0043c8f0) that transforms
    // some internal state into a 64-bit mask. The mask is then ORed into the flags.

    EntityBase* obj = this; // save original pointer (used for offsets after helper call)

    // Helper call: takes address of local 'obj' (simulating &param_1). 
    // The helper may modify 'obj' (e.g., resolve a sub-object), but we still use the original 'this'.
    FUN_0043c8f0(&obj);

    // Compute the 64-bit mask (likely a shifted value from the helper's outcome).
    // Note: __allshl is an MSVC intrinsic for 64-bit left shift. Decompiler shows no arguments,
    // but flags likely derived from helper result.
    uint64 mask = __allshl(); // actual shift amount and operand are implicit

    // Apply mask to the two 32-bit halves of the flag field
    uint32* lowFlags = (uint32*)((uint8*)obj + 0x148); // +0x148: low dword of flags
    uint32* highFlags = (uint32*)((uint8*)obj + 0x14c); // +0x14c: high dword of flags
    *lowFlags |= (uint32)(mask & 0xFFFFFFFF);
    *highFlags |= (uint32)(mask >> 32);
}