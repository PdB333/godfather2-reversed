// FUNC_NAME: RandomManager::generateNextRandom

uint32_t __fastcall RandomManager::generateNextRandom(uint32_t this) // this in ECX
{
    // Bit 10 (0x400) check: if the random generator is not ready, return sentinel
    // this->somePointer (offset +0x5c) -> state flags at +0x8e0
    if ((*(uint32_t *)(*(uint32_t *)(this + 0x5c) + 0x8e0) >> 10) & 1)
    {
        return 0xB05B8396; // Reserved "not available" value
    }

    uint32_t index = DAT_010c2678 & DAT_012054b4; // Combine global constants to get table index
    DAT_012054b4++; // Advance global counter

    // Access negative offset array using derived index
    // Uses floating point multiplier from table at DAT_010c2680
    // Convert result to int (truncation toward zero) and use negative as offset
    int offset = (int)(*(float *)((uint8_t *)&DAT_010c2680 + index * 4) * _DAT_00e445c0);
    return *(&DAT_00d65c04 - offset); // Equivalent to DAT_00d65c04[-offset]
}