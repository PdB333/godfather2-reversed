// FUNC_NAME: sin
double sin(float angle) {
    // Inline fsin wrapper for sine calculation (radians)
    double result;
    __asm {
        fld angle
        fsin
        fstp result
    }
    return result;
}