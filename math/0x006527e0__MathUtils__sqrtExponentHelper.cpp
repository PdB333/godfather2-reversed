// FUNC_NAME: MathUtils::sqrtExponentHelper
void __fastcall MathUtils::sqrtExponentHelper(uint floatBits, int subtractVal, uint unused, int& resultRef)
{
    // Computes exponent adjustment for fast approximate reciprocal square root / square root.
    // floatBits is the 32-bit representation of the input float (passed in EAX in the original asm).
    // subtractVal is an offset (likely 0x3F000000 or similar for the mantissa range).
    // The function computes: 
    //   unscaled = (floatBits - subtractVal) + 1; // as unsigned int
    //   floatUnscaled = (float)unscaled; // with special handling for negative signed conversion
    // then extracts the exponent (bits 23..30) from floatUnscaled and determines a rounding bit.
    // The result is passed via resultRef to a lower-level math func (FUN_0064b810).

    uint unscaledU = (floatBits - subtractVal) + 1;
    float fUnscaled = (float)(int)unscaledU; // signed conversion first to allow negative
    if ((int)unscaledU < 0) {
        fUnscaled += 4294967296.0f; // adjust for unsigned range (2^32)
    }

    int exp = ((uint)fUnscaled >> 0x17) & 0xFF; // bits [30:23] as integer
    int lowBit = ((unscaledU & (floatBits - subtractVal)) != 0) ? 1 : 0; // rounding bit from fractional part

    // Pass to low-level function: adjusted exponent = lowBit + exp - 0x7F
    // and a pointer to resultRef (which likely gets the final sqrt or exponent result)
    FUN_0064b810(lowBit + exp + -0x7F, &resultRef);
}