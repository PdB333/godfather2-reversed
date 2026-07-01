// FUNC_NAME: BitFlagContainer::getFlagAndId
// Function at 0x007ab500: Returns a packed value (high 24 bits = ID from this+0x58 low byte cleared, low 8 bits = bit test result)
// param_1 (this) - pointer to object with uint32 at +0x58 (packed pointer/ID)
// param_2 (bitIndex) - 0-based bit index into flag array at +0x249c relative to the pointer stored at this+0x58
uint32_t __thiscall BitFlagContainer::getFlagAndId(int32_t thisPtr, uint32_t bitIndex)
{
    // Packed data at this+0x58: low 8 bits are ignored (overwritten by result), high 24 bits are an ID
    uint32_t packedData = *(uint32_t*)(thisPtr + 0x58);
    // The packedData is also a pointer to a large structure containing the bitfield array at offset 0x249c
    uint32_t* bitfieldTable = (uint32_t*)packedData;
    // +0x249c is the offset to the start of a bitfield array (32 bits per slot)
    uint32_t wordIndex = bitIndex >> 5; // divide by 32
    uint32_t bitMask = 1 << (bitIndex & 0x1F);
    uint32_t flagWord = bitfieldTable[0x249c / 4 + wordIndex]; // DWORD index based on offset 0x249c
    bool flagSet = (flagWord & bitMask) != 0;
    // Combine: high 24 bits from packedData, low byte = flag result (0 or 1)
    return (packedData & 0xFFFFFF00) | (flagSet ? 1 : 0);
}