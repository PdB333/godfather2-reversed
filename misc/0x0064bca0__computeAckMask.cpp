// FUNC_NAME: computeAckMask
// Function at 0x0064bca0: Computes a bitmask with the lower N bits set, where N = param_1.
// Used in networking (likely TNL ack mask generation). Calls setBitInMask (0x0064b9e0) to set bit N,
// then masks off bits >= N (except when N == 0x20, which is a special case for full mask?).
uint32_t computeAckMask(uint8_t bitCount)
{
    uint32_t mask = 0;
    // Set bit at position bitCount in mask (modulo 32 handled by setBitInMask)
    setBitInMask(bitCount, &mask);
    // If bitCount is not 32, keep only bits 0..bitCount-1
    if (bitCount != 0x20) {
        mask &= (1 << (bitCount & 0x1f)) - 1;
    }
    return mask;
}