// FUNC_NAME: EntityBitfield::getPackedBitFlag
// Function at 0x00690210: Tests a bit in a bitfield array at offset +0x249c and returns packed result.
// The parameter 'index' encodes both a bit index (low 5 bits) and a group ID (bits 13-31).
// Return value: ((index >> 13) & 0xFFFFFF) << 8 | (1 if bit set else 0)
uint32 __thiscall getPackedBitFlag(uint index)
{
    // Bitfield array starts at this + 0x249c, each element is a 32-bit word
    uint32* bitArray = (uint32*)((uint8*)this + 0x249c);
    uint32 wordIndex = index >> 5;            // each word covers 32 bits
    uint32 bitMask = 1 << (index & 0x1F);     // target bit within word
    bool flag = (bitArray[wordIndex] & bitMask) != 0;
    // Pack the group ID (bits 13-31 of index) shifted to high 24 bits, and flag as low 8 bits
    return ((index >> 13) & 0xFFFFFF) << 8 | (uint8)flag;
}