// FUNC_NAME: Math::fixedMulShift16
// Function at 0x00676010 - Signed 32-bit fixed-point multiplication returning (a * b) >> 16
// Implements sign-handled multiplication returning the upper 16 bits of the 64-bit product.
// Uses __fastcall with first argument (a) in EAX, second (b) in EDX.
int __fastcall fixedMulShift16(int a, int b)
{
    int sign = 1;

    // Handle sign: take absolute values of a and b, determine final sign
    if (a < 0)
    {
        a = -a;
        sign = -1;
        if (b >= 0)
        {
            goto absoluteMultiply;
        }
        sign = 1;
    }
    else
    {
        sign = 1;
        if (b >= 0)
        {
            goto absoluteMultiply;
        }
        sign = -1;
    }
    // b is negative here; negate it to make positive
    b = -b;

absoluteMultiply:
    // Both a and b are now non-negative (unsigned)
    unsigned int ua = (unsigned int)a;
    unsigned int ub = (unsigned int)b;

    // Compute (a * b) >> 16 using 16-bit partial products
    // result = (a_lo*b_lo) >> 16 + a_lo*b_hi + a_hi*b_lo + a_hi*b_hi * 65536
    unsigned int productHigh = (( (ua & 0xFFFF) * (ub & 0xFFFF) ) >> 16)
                              + ((ub & 0xFFFF) * (ua >> 16))
                              + ((ua & 0xFFFF) * (ub >> 16))
                              + ((ua >> 16) * (ub >> 16) * 0x10000);

    // Apply sign
    return (int)productHigh * sign;
}