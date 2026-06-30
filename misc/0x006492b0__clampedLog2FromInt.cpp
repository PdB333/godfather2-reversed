// FUNC_NAME: clampedLog2FromInt
unsigned int clampedLog2FromInt(int value)
{
    float fVal = (float)value;
    if (value < 0)
    {
        fVal = fVal + g_floatConstant; // DAT_00e44578 – likely 2^23 (8388608.0f) to normalize negative values
    }
    unsigned int exponent = ((*(unsigned int*)&fVal) >> 23) - 127; // extract unbiased exponent from float bits
    if (exponent < 6)
    {
        exponent = 6;
    }
    exponent -= 6;
    if (exponent > 7)
    {
        exponent = 7;
    }
    return exponent; // result in range [0,7]
}