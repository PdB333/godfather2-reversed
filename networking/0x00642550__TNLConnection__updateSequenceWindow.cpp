// FUNC_NAME: TNLConnection::updateSequenceWindow

void __fastcall TNLConnection::updateSequenceWindow(int this, int in_EAX, int param_1)
{
    // this is in EDI (unaff_EDI in decompiled)
    int delta;
    uint* pSlot;
    uint currentValue;
    uint newValue;

    // Compute the difference between current sequence and base sequence, minus 1
    delta = (in_EAX - param_1) - 1;

    // Access the slot in the sequence window bit array
    // Structure: this->m_pWindowData (at offset 0) points to a data block
    // At offset +0x0C in that block is a pointer to an array of uint32 slots
    // Each slot indexed by param_1 (base sequence)
    pSlot = (uint*)(*(int*)(*(int*)this + 0x0C) + param_1 * 4);

    // Validate delta fits within the window size (0x1FFFF = 131071)
    if (0x1FFFF < (int)((delta ^ (delta >> 31)) - (delta >> 31))) {
        pSlot = (uint*)(*(int*)(this + 3));  // fallback pointer at this+12 (unaff_EDI[3])
        FUN_00638b80("control structure too long");
        // The extraout_ECX is ignored; delta remains as computed
    }

    // Update the slot value:
    // Low 6 bits are preserved; bits 6-31 are set to (delta + 0x1FFFF) * 64
    // The XOR pattern clears high bits, then XORs with the shifted value.
    // Equivalent to: *pSlot = ( *pSlot & 0x3F ) | ( ((delta + 0x1FFFF) * 64) & 0xFFFFC0 );
    currentValue = *pSlot;
    newValue = currentValue ^ (((delta + 0x1FFFF) * 0x40) ^ currentValue) & 0xFFFFC0;
    *pSlot = newValue;
}