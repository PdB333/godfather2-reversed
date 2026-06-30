// FUNC_NAME: atan_impl
// Address: 0x00417480
// Role: Computes arctangent of a float using x87 FPATAN (atan(x) = atan(x/1))
// Returns extended precision (80-bit) result.
long double atan_impl(float x) {
    long double result;
    __asm {
        fld x         // st(0) = x
        fld1          // st(0) = 1, st(1) = x
        fpatan        // st(0) = atan(st(1)/st(0)) = atan(x/1) = atan(x)
        fstp result   // store extended result
    }
    return result;
}