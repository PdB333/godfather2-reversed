// FUNC_NAME: distance3D
// 0x0042a160: Utility function to compute Euclidean distance between two 3D vectors
float distance3D(const float* vecA, const float* vecB)
{
    float dx = vecA[0] - vecB[0];
    float dy = vecA[1] - vecB[1];
    float dz = vecA[2] - vecB[2];
    return sqrtf(dx * dx + dy * dy + dz * dz);
}