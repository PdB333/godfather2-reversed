// FUNC_NAME: MathUtils::distSq
// Function address: 0x0045c470
// Computes squared Euclidean distance between two 3D vectors (float arrays of at least 3 elements)
float distSq(const float* a, const float* b)
{
    float dx = a[0] - b[0];
    float dy = a[1] - b[1];
    float dz = a[2] - b[2];
    return dx * dx + dy * dy + dz * dz;
}