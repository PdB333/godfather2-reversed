// FUNC_NAME: BitField::testBitWithId
uint32 __thiscall BitField::testBitWithId(int this, uint32 packedIndex)
{
    // Bit field array stored at offset 0x249c in the object
    uint32* bitField = (uint32*)((uint8*)this + 0x249c);
    uint32 wordIndex = packedIndex >> 5;
    uint32 bitMask = 1 << (packedIndex & 0x1F);
    bool flag = (bitField[wordIndex] & bitMask) != 0;
    // Pack the high bits (13-31) of the index with the boolean flag in low byte
    uint32 highPart = packedIndex >> 0xD;
    return (highPart << 8) | (flag ? 1 : 0);
}