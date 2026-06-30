// FUNC_NAME: atan2
// Function at 0x00464290: Wrapper around x87 FPATAN instruction to compute arctan(y/x) (atan2).
// Returns the angle in radians whose tangent is y/x, using the signs of both arguments.
// Uses 80-bit extended precision internally but returns a float.
float atan2(float y, float x) {
    // x87 stack: st(1) = y, st(0) = x
    // fpatan computes st(1) = arctan(st(1)/st(0)) and pops, result in st(0)
    long double result;
    __asm {
        fld x
        fld y
        fpatan
        fstp result
    }
    return static_cast<float>(result);
}