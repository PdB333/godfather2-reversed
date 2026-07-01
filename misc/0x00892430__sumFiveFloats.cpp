// FUNC_NAME: sumFiveFloats
// Function address: 0x00892430
// Role: Sums the first 5 float values in an array, returning extended precision result.
// Likely a utility for adding up float components (e.g., vector elements or aggregated stats).
double __fastcall sumFiveFloats(float* values)
{
    // Sum values[0] through values[4] with explicit casts to double for precision
    return (double)values[0] + (double)values[1] + (double)values[2] + (double)values[3] + (double)values[4];
}