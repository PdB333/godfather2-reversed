// FUNC_NAME: FlagSet::isBitSet
uint32_t __thiscall FlagSet::isBitSet(uint32_t bitIndex) {
    // Bit array at offset 0x2188 from 'this'.
    // bitIndex: bits 0-4 = bit in dword, bits 5+ = dword index.
    uint32_t* bitArray = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x2188);
    uint32_t dwordIndex = bitIndex >> 5;
    uint32_t bitMask = 1 << (bitIndex & 0x1F);
    bool result = (bitArray[dwordIndex] & bitMask) != 0;
    // Return low byte as boolean, upper bytes zero (original bitIndex high bits are zero in practice).
    return static_cast<uint32_t>(result);
}