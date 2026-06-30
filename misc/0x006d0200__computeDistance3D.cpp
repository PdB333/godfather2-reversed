// FUNC_NAME: computeDistance3D
#include <math.h>

// Computes Euclidean distance between two 3D points/vectors.
// Each point is assumed to have x, y, z at indices 0, 1, 2.
float computeDistance3D(float* p1, float* p2)
{
    float dx = p1[0] - p2[0];
    float dy = p1[1] - p2[1];
    float dz = p1[2] - p2[2];
    return sqrt(dx * dx + dy * dy + dz * dz);
}