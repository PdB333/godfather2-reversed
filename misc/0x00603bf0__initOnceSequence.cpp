// FUNC_NAME: initOnceSequence
// Function address: 0x00603bf0
// Role: One-time initialization sequence guarded by a flag at +0x4c (bit 3).
// Calls doStep() five times, then sets the guard flag.
void __thiscall initOnceSequence(void)
{
    // Check if bit 3 of the flags field (+0x4c) is zero (not yet initialized)
    if (((*(uint*)(this + 0x4c) >> 3) & 1) == 0) {
        // Execute the initialization sequence (five steps)
        doStep(this);
        doStep(this);
        doStep(this);
        doStep(this);
        doStep(this);
        // Mark the sequence as completed by setting bit 3
        *(uint*)(this + 0x4c) |= 8;
    }
}