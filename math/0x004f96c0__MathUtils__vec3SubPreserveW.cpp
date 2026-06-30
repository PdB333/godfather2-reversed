// FUNC_NAME: MathUtils::vec3SubPreserveW
void __fastcall MathUtils::vec3SubPreserveW(float* dest, float* a, float* b)
{
    // Subtract two 4-component vectors (a - b) into dest, preserving dest's w component (index 3)
    // This implements a 3D vector subtraction while keeping the homogeneous coordinate unchanged.
    // Address: 0x004f96c0
    float w = dest[3];
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    dest[3] = w;
}