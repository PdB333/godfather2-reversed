// FUNC_NAME: fsin
long double __cdecl fsin(float x)
{
    // Wrapper for x87 FSIN instruction (10-byte long double result)
    return (long double)fsin((long double)x); // Note: original FSIN takes st(0) and replaces with sin(st(0)), so direct call with x
}