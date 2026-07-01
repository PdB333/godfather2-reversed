// FUNC_NAME: Sentient::canPerformAction
// Address: 0x0093a000
// Role: Checks if the sentient entity is active and not in a prohibited state (e.g., stunned, dead, in cover, busy).
// Returns true if all conditions are met.

bool __thiscall Sentient::canPerformAction(void* thisPtr) {
    // +0x48: active flag (byte)
    if (*(char*)((int)thisPtr + 0x48) == '\0') {
        return false;
    }

    uint flags = *(uint*)((int)thisPtr + 0x5c);  // +0x5c: bitfield of states

    // Check that specific bits are clear:
    // Bit 22 (0x400000) – possibly "stunned" or "disabled"
    // Bit 3  (0x8)      – possibly "dead"
    // Bit 29 (0x20000000) – possibly "in cover" or "uncontrollable"
    // Bit 10 (0x400)    – possibly "busy" or "animating"
    if ((flags & (1 << 22)) != 0) return false;
    if ((flags & (1 << 3))  != 0) return false;
    if ((flags & (1 << 29)) != 0) return false;
    if ((flags & (1 << 10)) != 0) return false;

    return true;
}