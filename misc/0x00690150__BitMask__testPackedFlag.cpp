// FUNC_NAME: BitMask::testPackedFlag
// Address: 0x00690150
// Role: Tests a bit in a bitmask array and returns a packed value combining the high bits of the index and the test result.
//   - this: pointer to a BitMask object with a bit array at offset 0x8e0 (array of uint32)
//   - param_2: index (lower 5 bits determine bit within word, bits 5+ determine word index)
//   - return: ((index >> 13) << 8) | (bitValue ? 1 : 0)

uint32 __thiscall BitMask::testPackedFlag(uint32 index)
{
    // Bit array starting at offset +0x8e0; word index = index >> 5
    uint32* bitArray = (uint32*)((uint8*)this + 0x8e0);
    uint32 wordOffset = index >> 5;
    uint32 bitMask = 1 << (index & 0x1F);
    int32 bitValue = (bitArray[wordOffset] & bitMask) != 0 ? 1 : 0;

    // Pack the high 19 bits of the original index (bits 13+ shifted to bits 8-31) and the boolean into low byte
    return ( (index >> 0xD) << 8 ) | (bitValue & 0xFF);
}