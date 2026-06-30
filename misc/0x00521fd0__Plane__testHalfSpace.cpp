// FUNC_NAME: Plane::testHalfSpace

// Global threshold used for plane half-space testing (address 0x00e2b05c)
extern float g_planeThreshold;

// Tests if the projection of vector (pointA - pointB) onto the plane normal is >= g_planeThreshold.
// The plane normal is stored in the 'this' pointer (array of 3 floats).
// Returns 1 if true, 0 otherwise.
int __thiscall Plane::testHalfSpace(float *pointA, float *pointB)
{
    float dot = this[0] * (pointA[0] - pointB[0]) +
                this[1] * (pointA[1] - pointB[1]) +
                this[2] * (pointA[2] - pointB[2]);

    if (dot >= g_planeThreshold)
        return 1;
    else
        return 0;
}