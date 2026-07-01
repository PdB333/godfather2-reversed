// FUNC_NAME: MathUtils::quaternionCrossProduct
// Address: 0x007d2090
// Computes the cross product of two 3D vectors (imaginary parts of quaternions)
// and stores the result into the first three components of a quaternion,
// preserving the original scalar component (W) of the output.
// Parameters:
//   outQuat: destination quaternion (float[4]) - in EAX/ECX
//   vecA: source vector (float[4], only first 3 used)
//   vecB: source vector (float[4], only first 3 used)
void __fastcall quaternionCrossProduct(float *outQuat, float *vecA, float *vecB)
{
    float ax = vecA[0];
    float ay = vecA[1];
    float az = vecA[2];
    // vecA[3] is ignored (read but not used)
    float bx = vecB[0];
    float by = vecB[1];
    float bz = vecB[2];
    // vecB[3] is read but only used in a self-cancelling expression
    float savedW = outQuat[3];          // Preserve original scalar component

    outQuat[0] = by * az - bz * ay;    // Cross product x
    outQuat[1] = bz * ax - bx * az;    // Cross product y
    outQuat[2] = bx * ay - by * ax;    // Cross product z
    // The following line computes 0.0f (vecB[3]*vecA[3] - vecB[3]*vecA[3]) and discards it
    outQuat[3] = 0.0f;                 // Overwrite with zero (then restore)
    outQuat[3] = savedW;               // Restore original W
}