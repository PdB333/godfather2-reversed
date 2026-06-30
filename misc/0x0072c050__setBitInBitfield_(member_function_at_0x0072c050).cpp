// FUNC_NAME: setBitInBitfield (member function at 0x0072c050)
void __thiscall SomeClass::setBitInBitfield(uint bitIndex)
{
    // Bitfield stored at this+0x2188; array of uint32 for 32-bit granularity
    uint* bitWord = reinterpret_cast<uint*>(this + 0x2188 + ((bitIndex >> 5) * 4));
    *bitWord |= (1 << (bitIndex & 0x1f));
}