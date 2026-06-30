// FUNC_NAME: FixedPairArray::add
void __thiscall FixedPairArray::add(uint32_t first, uint32_t second)
{
    uint32_t count = *(uint32_t *)(this + 0x88); // current number of pairs
    if (count < 0x10) // max 16 pairs
    {
        // Array base at this+0x8, each pair is 8 bytes (two uint32s)
        *(uint32_t *)(this + 0x8 + (count * 0x8)) = first;   // first value
        *(uint32_t *)(this + 0xC + (count * 0x8)) = second;  // second value
        *(uint32_t *)(this + 0x88) = count + 1;              // increment count
    }
}