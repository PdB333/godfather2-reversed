// FUNC_NAME: setDiagonalDirectionVector
// Address: 0x00601970
// Sets a 3-element float array to (param1, 0.0, param1) – likely a direction vector in the XZ plane.
// The two called functions (FUN_00b99fcb, FUN_00b99e20) are unknown; they do not affect the output.

void setDiagonalDirectionVector(float angle, float* outVec)
{
    outVec[1] = 0.0f; // Y component always zero

    double dAngle = (double)angle;
    FUN_00b99fcb(); // unknown side-effect function
    outVec[0] = (float)dAngle; // X component = angle

    dAngle = (double)angle;
    FUN_00b99e20(); // unknown side-effect function
    outVec[2] = (float)dAngle; // Z component = angle
}