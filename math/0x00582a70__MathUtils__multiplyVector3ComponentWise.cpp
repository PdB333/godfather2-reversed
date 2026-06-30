// FUNC_NAME: MathUtils::multiplyVector3ComponentWise
// Address: 0x00582a70
// Role: Multiply the first three components of two 4-element float vectors component-wise,
//       leaving the fourth component of the output vector unchanged.
// Note: This function uses __fastcall convention (ECX = outVec, EDX = vecA, stack = vecB).

void __fastcall multiplyVector3ComponentWise(float* outVec, float* vecA, float* vecB)
{
    // Load components from first vector (y, z, w)
    float ay = vecA[1];  // +0x04
    float az = vecA[2];  // +0x08
    float aw = vecA[3];  // +0x0C

    // Load components from second vector (y, z, w)
    float by = vecB[1];  // +0x04
    float bz = vecB[2];  // +0x08
    float bw = vecB[3];  // +0x0C

    // Preserve the original w component of the output
    float origOutW = outVec[3]; // +0x0C

    // Component-wise multiply the first three components (x,y,z)
    outVec[0] = vecA[0] * vecB[0]; // out.x = a.x * b.x
    outVec[1] = ay * by;           // out.y = a.y * b.y
    outVec[2] = az * bz;           // out.z = a.z * b.z

    // Compute the w product but then discard it, restoring the original w
    outVec[3] = aw * bw;           // product computed (unused)
    outVec[3] = origOutW;          // restore original w

    return;
}