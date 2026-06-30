// FUNC_NAME: calculateTangent
long double __thiscall calculateTangent(float angle)
{
    long double result;
    __asm
    {
        fld [angle]       // Load angle (32-bit float, converts to extended)
        fptan             // Compute tan(angle); pushes 1.0 and tan(angle)
        fnstsw ax         // Check for exceptions (optional)
        fstp st(0)        // Pop the 1.0
        fstp [result]     // Pop and store tan(angle)
    }
    return result;
}