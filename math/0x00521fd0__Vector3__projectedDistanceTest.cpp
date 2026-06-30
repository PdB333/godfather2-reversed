// FUNC_NAME: Vector3::projectedDistanceTest
// Function address: 0x00521fd0
// Reconstructed C++ code for a member function of a 3D vector class.
// It tests whether the dot product of 'this' (as a direction vector) with
// the difference between param_1 and param_2 is at least a global threshold.
// Uses a global constant (DAT_00e2b05c) likely 0.0f for half‑space checks.

// Header: assume class Vector3 has float x, y, z.

bool Vector3::projectedDistanceTest(const float* pointA, const float* pointB) const
{
    // this: pointer to Vector3 (3 floats)
    // pointA – first point (3 floats)
    // pointB – second point (3 floats)
    // Global threshold (likely 0.0f or small epsilon)
    extern float g_ProjectionThreshold; // DAT_00e2b05c

    // Compute dot product: this · (pointA - pointB)
    float dx = pointA[0] - pointB[0];
    float dy = pointA[1] - pointB[1];
    float dz = pointA[2] - pointB[2];

    float dot = this->x * dx + this->y * dy + this->z * dz;

    // Return true if projection is at least the threshold
    return (dot >= g_ProjectionThreshold);
}