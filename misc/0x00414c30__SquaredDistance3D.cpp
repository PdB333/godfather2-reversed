// FUNC_NAME: SquaredDistance3D
float SquaredDistance3D(const float* pointA, const float* pointB)
{
    // Compute squared Euclidean distance between two 3D points: (dx)^2 + (dy)^2 + (dz)^2
    float dx = pointA[0] - pointB[0];
    float dy = pointA[1] - pointB[1];
    float dz = pointA[2] - pointB[2];
    return dx * dx + dy * dy + dz * dz;
}