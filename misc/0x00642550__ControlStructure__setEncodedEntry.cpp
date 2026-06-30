// FUNC_NAME: ControlStructure::setEncodedEntry
void __fastcall ControlStructure::setEncodedEntry(int param_1) // param_1 is EDX (likely index)
{
    int in_EAX; // EA register - likely the encoded value (or some offset)
    uint uVar1;
    uint extraout_ECX;
    uint *puVar2;
    int *unaff_EDI; // Base pointer to this structure

    // Compute difference: in_EAX - param_1 - 1. This is a sanity check for control structure length.
    uVar1 = (in_EAX - param_1) - 1;
    // Access the buffer pointer at offset +0xC from *this (the first member points to a control block)
    puVar2 = (uint *)(*(int *)(*unaff_EDI + 0xC) + param_1 * 4);

    // Check that the absolute value of (in_EAX - param_1 - 1) is <= 0x1FFFF (131071).
    if (0x1FFFF < (int)((uVar1 ^ (int)uVar1 >> 0x1F) - ((int)uVar1 >> 0x1F))) {
        // If out of range, use fallback buffer stored at this[3] (offset +0xC in the structure)
        puVar2 = (uint *)unaff_EDI[3];
        FUN_00638b80("control structure too long"); // Debug assert/error
        uVar1 = extraout_ECX; // Restore uVar1 from leftover ECX? Probably a compiler optimization artifact
    }

    // Update the 32-bit value at *puVar2:
    // Preserve low 6 bits (0x3F), replace bits 6-31 with (uVar1 + 0x1FFFF) << 6
    // This encodes a block index/offset with room for 6-bit flags.
    *puVar2 = (*puVar2 & 0x3F) | ((uVar1 + 0x1FFFF) << 6);
}