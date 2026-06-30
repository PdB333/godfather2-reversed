// FUNC_NAME: sqrtFloat
float __cdecl sqrtFloat(float value)
{
    // Wrapper around the internal SQRT intrinsic for extended precision
    return (float)SQRT((long double)value);
}