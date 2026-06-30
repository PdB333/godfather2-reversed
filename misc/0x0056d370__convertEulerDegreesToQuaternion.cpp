// FUNC_NAME: convertEulerDegreesToQuaternion
void __cdecl convertEulerDegreesToQuaternion(float degreesX, float degreesY, float degreesZ, float* outQuaternion)
{
    // Global constant likely π/180 for degrees to radians conversion
    float radX = DAT_00e2cd54 * degreesX;
    float radY = DAT_00e2cd54 * degreesY;
    float radZ = DAT_00e2cd54 * degreesZ;

    // Compute sine and cosine for each angle
    double dTemp = (double)radX;
    FUN_00b99fcb();  // cosf? – likely standard library functions
    float cosX = (float)dTemp;
    dTemp = (double)radX;
    FUN_00b99e20();  // sinf?
    float sinX = (float)dTemp;

    dTemp = (double)radY;
    FUN_00b99fcb();
    float cosY = (float)dTemp;
    dTemp = (double)radY;
    FUN_00b99e20();
    float sinY = (float)dTemp;

    dTemp = (double)radZ;
    FUN_00b99fcb();
    float cosZ = (float)dTemp;
    dTemp = (double)radZ;
    FUN_00b99e20();
    float sinZ = (float)dTemp;

    // 1 - cosX and 1 - sinX (used in quaternion formula)
    float oneMinusCosX = DAT_00e44564 - cosX;
    float oneMinusSinX = DAT_00e44564 - sinX;

    // Compute quaternion components (order: x, y, z, w)
    // Derived from a non‑standard Euler to quaternion conversion
    outQuaternion[0] = sinX * cosY * sinZ + sinY * cosX * cosZ;
    outQuaternion[1] = oneMinusSinX * cosY * cosZ + sinY * cosX * sinZ;
    outQuaternion[2] = oneMinusCosX * cosY * sinZ + sinY * sinX * cosZ;
    outQuaternion[3] = cosX * cosY * cosZ + sinY * sinX * sinZ;
}