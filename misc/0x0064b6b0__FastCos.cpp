// FUNC_NAME: FastCos
// Function address: 0x0064b6b0
// Calculates cosine of a float using x87 FCOS instruction.
// Returns long double (80-bit extended precision) result.

long double FastCos(float value)
{
    long double result;
    // Inline x87 FCOS: expects ST(0) = angle in radians, pushes cosine.
    __asm__ __volatile__ (
        "fcos"
        : "=t" (result)
        : "0" ((long double)value)
    );
    return result;
}