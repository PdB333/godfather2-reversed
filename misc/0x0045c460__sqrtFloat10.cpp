// FUNC_NAME: sqrtFloat10
long double sqrtFloat10(float param_1)
{
    // Wraps x87 FSQRT instruction for extended-precision (80-bit) square root
    return sqrtl(param_1);
}