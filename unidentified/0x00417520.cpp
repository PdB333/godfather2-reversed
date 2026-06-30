// FUN_00417520: mathComputeSinCos
// Function address: 0x00417520
// Computes both sine and cosine of the given angle (in radians) and returns them via pointers.
// Calls internal sin/cos implementations at 0x00b99fcb and 0x00b99e20.

void mathComputeSinCos(float angle, float* outSin, float* outCos)
{
    double dAngle = (double)angle;

    // Internal sine function
    double sinResult = mathInternalSin(dAngle); // calls FUN_00b99fcb
    *outSin = (float)sinResult;

    dAngle = (double)angle;
    // Internal cosine function
    double cosResult = mathInternalCos(dAngle); // calls FUN_00b99e20
    *outCos = (float)cosResult;
}