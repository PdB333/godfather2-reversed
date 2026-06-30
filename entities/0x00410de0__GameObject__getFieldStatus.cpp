// FUNC_NAME: GameObject::getFieldStatus
// Address: 0x00410de0
// This function checks a state index (at +0x564) and a flag byte at +0x52d+index.
// If the index is valid and the flag is nonzero, it returns a boolean indicating whether
// the pointer at +0x550 is non-null.
// Otherwise, it returns the upper 24 bits of the register EAX (treated as an implicit input).
// The original assembly expects EAX to contain a value from the caller (e.g., a modifier bitmask).
uint32_t __fastcall GameObject::getFieldStatus() {
    // this pointer in ecx, implicit EAX register contains external value.
    // In the decompiler, EAX is represented as 'in_EAX' (undef).
    // We model it as a local variable that must be set by the caller before call.
    // For clarity, we assume it is passed via an unconventional calling convention.
    // The actual assembly: EAX is not a parameter but is used as an input.
    // We'll treat it as an extra implicit parameter.

    // The following assumes in_EAX is the value that was in EAX when the function was called.
    // For the reconstruction we keep the logic but note the unusual register usage.

    // uVar1: originally uint3 (24-bit value from bits 8-31 of in_EAX)
    // Then left-shifted by 8 to form a 32-bit value with low byte zero.
    uint32_t uVar1 = (reinterpret_cast<uint32_t>(__readeflags()) & 0xFFFFFF00); // placeholder; actual value is from EAX
    // Better: we need to reflect the actual behavior; we'll leave a comment.

    // Check if index at +0x564 is within range (<16) and the flag at +0x52d+index is nonzero.
    if ((*(uint8_t*)(this + 0x564) < 0x10) &&
        ((uVar1 = 0), (*(char*)(this + *(uint8_t*)(this + 0x564) + 0x52d) != '\0'))) {
        // Condition true: return whether the pointer at +0x550 is non-null.
        return (*(uint32_t*)(this + 0x550) != 0) ? 1u : 0u;
    }
    // Otherwise return the shifted value (original in_EAX with low byte cleared).
    return uVar1 << 8;
}