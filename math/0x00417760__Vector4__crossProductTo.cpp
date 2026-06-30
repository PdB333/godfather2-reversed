// FUNC_NAME: Vector4::crossProductTo
// Function at 0x00417760: Computes the cross product of two 4D vectors (this x other) and stores the result.
// The w component is set to zero (since cross product of 3D vectors yields a vector perpendicular to both).
// Parameters:
//   this (in EAX): the 'this' pointer, a 4-float vector (x, y, z, w)
//   param_1: pointer to the 'other' 4-float vector
//   param_2: pointer to the output 4-float vector (result)
void __thiscall Vector4::crossProductTo(const float* thisVec, const float* otherVec, float* outVec)
{
    // Load components of this vector (via 'this' pointer, passed in EAX)
    float ax = thisVec[0];  // +0x00
    float ay = thisVec[1];  // +0x04
    float az = thisVec[2];  // +0x08
    float aw = thisVec[3];  // +0x0C  // w component (unused for cross product)

    // Load components of the other vector (explicit parameter)
    float bx = otherVec[0];
    float by = otherVec[1];
    float bz = otherVec[2];
    float bw = otherVec[3];

    // Compute cross product: result = this x other
    // x = ay*bz - az*by
    // y = az*bx - ax*bz
    // z = ax*by - ay*bx
    // w = 0 (cross product of 3D vectors has no w component)
    outVec[0] = ay * bz - az * by;
    outVec[1] = az * bx - ax * bz;
    outVec[2] = ax * by - ay * bx;
    outVec[3] = 0.0f; // w = aw*bw - aw*bw, which is always 0
}