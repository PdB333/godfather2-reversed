// FUNC_NAME: MathUtils::zeroVector6
void __thiscall zeroVector6(float *vec) // 0x0052fae0
{
    // Zero out a 6-element float vector (e.g., 3D position + 3D velocity, or 6-DOF transform)
    vec[0] = vec[0] * 0.0f; // +0x00
    vec[1] = vec[1] * 0.0f; // +0x04
    vec[2] = vec[2] * 0.0f; // +0x08
    vec[3] = vec[3] * 0.0f; // +0x0C
    vec[4] = vec[4] * 0.0f; // +0x10
    vec[5] = vec[5] * 0.0f; // +0x14
}