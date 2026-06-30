// FUNC_NAME: Math::fixedPointDiv_16_16
// Address: 0x00676090
// Role: 16.16 signed fixed-point division (dividend / divisor returns Q16.16 result)
// Handles negative numbers by taking absolute values and re-applying sign.
// Standard algorithm: integer quotient + fractional part from remainder scaled to 16 bits.

int __fastcall fixedPointDiv_16_16(int dividend, int divisor)
{
    int sign = 1;

    // Handle negative dividend
    if (dividend < 0)
    {
        dividend = -dividend;
        sign = -1;
        if (divisor >= 0) // sign determined by divisor
            sign = -1;
        else
            sign = 1;
    }
    else
    {
        sign = 1;
        if (divisor < 0)
        {
            divisor = -divisor;
            sign = -1;
        }
    }

    // At this point both are positive
    unsigned int uDividend = (unsigned int)dividend;
    unsigned int uDivisor  = (unsigned int)divisor;

    // Integer part (scaled by 65536)
    unsigned int intPart = uDividend / uDivisor;
    unsigned int remainder = uDividend % uDivisor;

    // Normalize remainder to 16-bit fraction: shift remainder right until it fits in 16 bits
    // (while remainder >= 0x10000, shift both remainder and divisor right by 1)
    while (remainder >= 0x10000)
    {
        remainder >>= 1;
        uDivisor >>= 1;
    }

    // Fractional part: (remainder << 16) / divisor, then add integer part scaled
    unsigned int fracPart = (remainder << 16) / uDivisor;
    unsigned int result = intPart * 0x10000 + fracPart;

    // Apply sign
    return (int)result * sign;
}