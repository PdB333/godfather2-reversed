// FUNC_NAME: TNLConnection::checkSequenceMaskShift
bool TNLConnection::checkSequenceMaskShift()
{
    // +0x00: low 32 bits of the 64-bit sequence mask
    uint32_t maskLow = this->m_sequenceMaskLow;
    // +0x04: high 32 bits of the 64-bit sequence mask
    uint32_t maskHigh = this->m_sequenceMaskHigh;
    uint64_t fullMask = ((uint64_t)maskHigh << 32) | maskLow;

    // Test shifts by 0, 8, 16, 24 bits (multiples of a byte)
    for (uint32_t shift = 0; shift < 0x20; shift += 8)
    {
        // First 64-bit left shift of the mask by 'shift' bits
        uint64_t shiftedFirst = fullMask << shift;

        // Second 64-bit left shift (likely of a different value or constant,
        // but decompilation shows same mask; possibly a decompiler artifact)
        uint64_t shiftedSecond = fullMask << shift;

        // Build a masked version of the first shift: (high word & maskHigh) << 32 | (low word & maskLow)
        uint64_t maskedShift = ((uint64_t)((uint32_t)(shiftedFirst >> 32) & maskHigh) << 32)
                              | ((uint32_t)shiftedFirst & maskLow);

        // If the second shift matches this masked version, the pattern is found
        if (shiftedSecond == maskedShift)
        {
            return true;
        }
    }
    return false;
}