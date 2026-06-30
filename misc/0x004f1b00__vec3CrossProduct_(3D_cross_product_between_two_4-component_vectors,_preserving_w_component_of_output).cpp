// FUNC_NAME: vec3CrossProduct (3D cross product between two 4-component vectors, preserving w component of output)
void __fastcall vec3CrossProduct(float* outVec, const float* vecA, const float* vecB)
{
    // outVec is passed in EAX (output pointer), vecA in param_2, vecB in param_3
    // All pointers point to 4-float arrays (e.g., [x, y, z, w])
    float ax = vecA[0];
    float ay = vecA[1];
    float az = vecA[2];
    // aw = vecA[3]; // w component not used in cross product

    float bx = vecB[0];
    float by = vecB[1];
    float bz = vecB[2];
    // bw = vecB[3]; // w component not used

    // Compute cross product: out = a x b
    outVec[0] = ay * bz - az * by; // y1*z2 - z1*y2
    outVec[1] = az * bx - ax * bz; // z1*x2 - x1*z2
    outVec[2] = ax * by - ay * bx; // x1*y2 - y1*x2

    // The original code saves and restores outVec[3] (w component), leaving it unchanged
    // outVec[3] remains as it was before the call
    // No return value (void)
}