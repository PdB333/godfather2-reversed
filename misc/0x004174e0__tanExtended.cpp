// FUNC_NAME: tanExtended
// Function address: 0x004174e0
// Wrapper around x87 fptan instruction, returns extended precision tangent (10 bytes).
// Input: float angle in radians; output: long double (80-bit) tangent value.
long double tanExtended(float angle) {
    long double result;
    __asm {
        fld  angle      // convert float to 80-bit extended double
        fptan           // ST(0) = 1.0, ST(1) = tan(angle)
        fstp result     // pop and store the 1.0, leaving tan(angle) on stack for return
    }
    return result;
}