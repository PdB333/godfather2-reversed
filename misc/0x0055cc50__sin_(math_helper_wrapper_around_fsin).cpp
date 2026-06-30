// FUNC_NAME: sin (math helper wrapper around fsin)
// Address: 0x0055cc50
// Wrapper for x87 fsin instruction. Takes a float (32-bit) and returns extended precision (80-bit).
long double sin(float x)
{
    return fsin(x); // fsin intrinsic or inline assembly equivalent
}