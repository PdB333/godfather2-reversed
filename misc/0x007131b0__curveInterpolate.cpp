// FUNC_NAME: curveInterpolate
// Function at 0x007131b0: Given an integer index and an integer input, maps the input through a linear curve segment defined by two float arrays (g_curveStartValues and g_curveEndValues) and a range constant (g_curveRange). Treats signed integers as unsigned by adding 2^32 if negative before division.
// Constants: g_curveRange (DAT_00e5175c) and g_curveShift (DAT_00e44578 = 4294967296.0).
// The curve segment is indexed by param_1*2 (two floats per segment: start and end).
// Returns: start + (end - start) * (unsignedInput / unsignedRange)

extern float g_curveStartValues[];   // DAT_0112aca0
extern float g_curveEndValues[];     // DAT_0112aca4
extern long double g_curveRange;     // DAT_00e5175c (as int, converted to long double)
extern long double g_curveShift;     // DAT_00e44578 = 4294967296.0 (2^32)

long double FUN_007131b0(int param_1, int param_2)
{
    long double fVar1 = (long double)param_2;
    long double fVar2;

    // Convert signed integer to unsigned by adding 2^32 if negative
    if (param_2 < 0) {
        fVar1 = fVar1 + g_curveShift;
    }

    fVar2 = g_curveRange;
    if ((int)g_curveRange < 0) {   // g_curveRange is stored as int; check sign
        fVar2 = fVar2 + g_curveShift;
    }

    // Interpolate: start + (end - start) * (input / range)
    return (fVar1 * ( (long double)(*(float*)(g_curveEndValues + param_1 * 2)) -
                      (long double)(*(float*)(g_curveStartValues + param_1 * 2)) ) /
            fVar2) +
           (long double)(*(float*)(g_curveStartValues + param_1 * 2));
}