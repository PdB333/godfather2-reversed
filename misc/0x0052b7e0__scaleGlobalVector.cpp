// FUNC_NAME: scaleGlobalVector
// Function at 0x0052b7e0: Multiply a global 4-component vector (likely a 3D vector + pad or a quaternion) by a scalar.
// The global floats are consecutive at addresses 0x01125260-0x0112526c.
extern float g_globalVector[4]; // or struct Vector4 { float x, y, z, w; };

void __cdecl scaleGlobalVector(float scalar)
{
    g_globalVector[0] *= scalar;
    g_globalVector[1] *= scalar;
    g_globalVector[2] *= scalar;
    g_globalVector[3] *= scalar;
}