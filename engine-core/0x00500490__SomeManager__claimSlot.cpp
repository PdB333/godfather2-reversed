// FUNC_NAME: SomeManager::claimSlot
// Address: 0x00500490
// Notes: This function claims a slot in a per-thread structure.
// It sets a "used" flag (bit 0) on a uint located at a base offset
// (from the object) plus a value from TLS slot index 2.
// The object fields: +0x10 base pointer, +0x2c flags byte,
// +0x30 some pointer, +0x35 a zero-check byte.
// The TLS value is likely a unique thread index or offset.

int __thiscall SomeManager::claimSlot(int thisPtr)
{
    uint *pSlot;
    int baseOffset;
    int threadOffset;

    // Conditionally call an initialization function if certain flags are set.
    // (byte at +0x2c & 2) indicates some mode,
    // pointer at +0x30 non-null and char at +0x35 zero likely mean "not yet initialized".
    if (((*(byte *)(thisPtr + 0x2c) & 2) != 0) &&
        (*(int *)(thisPtr + 0x30) != 0) &&
        (*(char *)(thisPtr + 0x35) == '\0'))
    {
        FUN_004b1ca0();  // Could be a lazy initializer
    }

    baseOffset = *(int *)(thisPtr + 0x10);               // +0x10: base address of a table or buffer
    threadOffset = *(int *)(*(int **)(__readfsdword(0x2c)) + 8); // TLS slot 2 -> per-thread offset
    pSlot = (uint *)(baseOffset + threadOffset);
    *pSlot = *pSlot | 1;  // Mark slot as used/reserved
    return (int)pSlot;
}