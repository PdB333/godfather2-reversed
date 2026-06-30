// FUN_004a2540: math::computeDirectionVector
void computeDirectionVector(float *outVector, float angle1, float angle2)
{
    // These functions likely compute sin and cos using x87 FPU instructions.
    // FUN_00b99e20 -> sinFunction
    // FUN_00b99fcb -> cosFunction
    double sinAngle1 = (double)angle1;
    sinAngle1 = sinFunction(sinAngle1);  // sin(angle1)

    double cosAngle2 = (double)angle2;
    cosAngle2 = cosFunction(cosAngle2);  // cos(angle2)

    double tempAngle = (double)angle1;

    // DAT_00e44564 is a constant, likely 1.0f
    outVector[0] = DAT_00e44564 - (float)cosAngle2 * (float)sinAngle1;

    // Re-use cosFunction, but the result is not captured; store original angle1?.
    // This may actually be sin(angle1) after a cos call on the FPU stack.
    cosFunction(/* unspecified */);
    outVector[1] = (float)tempAngle;  // could be sin(angle1) but decompiler shows original value

    cosAngle2 = (double)angle2;
    cosAngle2 = sinFunction(cosAngle2);  // sin(angle2)

    outVector[2] = DAT_00e44564 - (float)cosAngle2 * (float)sinAngle1;
}