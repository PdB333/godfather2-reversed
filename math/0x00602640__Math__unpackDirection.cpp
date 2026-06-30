// FUNC_NAME: Math::unpackDirection
#include <cmath>

// Constants for converting 12-bit angle values to radians
extern const float kAngleScale1; // = 2π / 4096 (or similar)
extern const float kAngleScale2; // = 2π / 4096 (or similar)

// Function at 0x00602640: Converts a packed 24-bit angle (two 12-bit components) into a unit direction vector.
// Input: packedAngle (in EAX) - low 12 bits = theta (elevation), high 12 bits = phi (azimuth)
// Output: outVec (pointed by ESI) - 3 floats: x, y, z
void Math::unpackDirection(uint packedAngle, float* outVec)
{
    // Special case: zero angle means straight up (0,1,0)
    if (packedAngle == 0)
    {
        outVec[0] = 0.0f;
        outVec[1] = 1.0f;
        outVec[2] = 0.0f;
        return;
    }

    // Extract and scale the two 12-bit angle components
    float theta = (float)(packedAngle & 0xFFF) * kAngleScale1; // elevation
    float phi   = (float)((packedAngle >> 12) & 0xFFF) * kAngleScale2; // azimuth

    // Compute spherical coordinates (y-up)
    float cosTheta = cosf(theta);
    float sinTheta = sinf(theta);
    float cosPhi   = cosf(phi);
    float sinPhi   = sinf(phi);

    outVec[0] = sinTheta * cosPhi; // x
    outVec[1] = cosTheta;          // y
    outVec[2] = sinTheta * sinPhi; // z
}