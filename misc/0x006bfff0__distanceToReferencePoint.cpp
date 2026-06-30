// FUNC_NAME: distanceToReferencePoint
// Function at 0x006bfff0: computes Euclidean distance from a given 3D point to a reference point obtained from system function FUN_00424fb0.
float __cdecl distanceToReferencePoint(float* position)
{
    float refX;
    float refY;
    float refZ;

    // Retrieve reference point (likely player/camera position). Second parameter 0 may indicate coordinate system or slot.
    FUN_00424fb0(&refX, 0);

    // The stack layout after the call: refX at lowest, refY next, refZ next (as declared).
    // position[0]=X, position[1]=Y, position[2]=Z
    double dx = (double)position[0] - (double)refX;
    double dy = (double)position[1] - (double)refY;
    double dz = (double)position[2] - (double)refZ;

    return SQRT(dx * dx + dy * dy + dz * dz);
}