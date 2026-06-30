// FUNC_NAME: scaleVector4
// Function address: 0x005161c0
// Description: Scales the first four floats pointed to by the pointer (passed in EAX) by the scalar parameter.
// Likely a helper function for 4-component vector or quaternion scaling.
// Calling convention unknown; pointer assumed to be first argument in EAX, scalar second.
// Reconstructed as a regular C function for clarity.

void scaleVector4(float *vec, float scalar)
{
    vec[0] *= scalar;
    vec[1] *= scalar;
    vec[2] *= scalar;
    vec[3] *= scalar;
}