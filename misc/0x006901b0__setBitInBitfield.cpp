// FUNC_NAME: setBitInBitfield
// Function address: 0x006901b0
// Sets a bit in a bitfield array at offset 0x249c. Used by various game systems for flag management.

void __thiscall setBitInBitfield(void* this, uint32 bitIndex)
{
    // Calculate pointer to the correct 32-bit word in the bitfield
    uint32* bitfieldWord = (uint32*)((uint8*)this + 0x249c + ((bitIndex >> 5) * 4));
    // Set the bit within that word
    *bitfieldWord |= (1 << (bitIndex & 0x1f));
}