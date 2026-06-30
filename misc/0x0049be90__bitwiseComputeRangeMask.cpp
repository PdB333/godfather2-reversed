// FUNC_NAME: bitwiseComputeRangeMask
uint __fastcall bitwiseComputeRangeMask(int unusedECX, int param2, uint param3, byte startBit)
{
    /* This utility computes a bitmask that isolates a range of bits.
       The range length is derived from the lower byte of a value passed in EAX
       (likely from caller context). The param2 value provides a secondary offset
       (its high 24 bits are used). The final mask is XORed and ANDed with param3.
       
       The algorithm:
       1. Compute rangeLengthMinusOne = (lowByteOfEAX - 1).
       2. Find the highest set bit position in that value (shift from 15 down).
       3. rangeEndBits = that bit position + 1 (or 0 if input was 0).
       4. Build two masks using CONCAT31(a,b):
          - mask1: bits from (startBit + rangeEndBits) upward, combined with high 24 bits of rangeLengthMinusOne.
          - mask2: bits from startBit upward, combined with high 24 bits of param2.
       5. XOR them and mask with param3.
       The effect is to produce a mask that covers bits [startBit, startBit+rangeEndBits-1].
    */
    byte rangeEndBits = 0;
    int rangeLengthMinusOne = (in_EAX & 0xFF) - 1; // low byte of EAX - 1
    short bitPosition = 0xF; // start from bit 15 (max for 16-bit value)
    unsigned short shortVersion = (unsigned short)rangeLengthMinusOne;

    if (shortVersion != 0) {
        // Find the highest set bit (leading zeros)
        while ((shortVersion >> bitPosition) == 0) {
            bitPosition--;
        }
    }

    if (shortVersion != 0) {
        rangeEndBits = (char)bitPosition + 1; // number of bits to cover range
    }

    // Build masks: combine a 24-bit high part with an 8-bit low part
    uint mask1 = CONCAT31((int3)((uint)rangeLengthMinusOne >> 8), -1 << ((rangeEndBits + startBit) & 0x1F));
    uint mask2 = CONCAT31((int3)((uint)param2 >> 8), -1 << (startBit & 0x1F));

    return (mask1 ^ mask2) & param3;
}