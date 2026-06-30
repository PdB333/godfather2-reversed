// FUNC_NAME: decodeGamepadButtonFlags
// Address: 0x004aa860
// Role: Translates a raw 16-bit input flags mask into a 4-bit gamepad button state mask.
// The input contains pairs of bits (bit0+bit8, bit1+bit8, bit0+bit9, bit1+bit9).
// The output bit0 is set if (bit0+bit8) are both set.
// Output bits 1-3 are set if the corresponding pair is NOT both set.
// This is likely used to convert low-level controller data into button presses for the EARS engine.

byte __fastcall decodeGamepadButtonFlags(uint inputFlags)
{
    byte result = 0;

    // Pair (bit0, bit8): both set -> output bit0 = 1
    if ((inputFlags & 0x101) == 0x101)
        result |= 1;

    // Pair (bit1, bit8): not both set -> output bit1 = 1
    if ((inputFlags & 0x102) != 0x102)
        result |= 2;

    // Pair (bit0, bit9): not both set -> output bit2 = 1
    if ((inputFlags & 0x201) != 0x201)
        result |= 4;

    // Pair (bit1, bit9): not both set -> output bit3 = 1
    if ((inputFlags & 0x202) != 0x202)
        result |= 8;

    return result;
}