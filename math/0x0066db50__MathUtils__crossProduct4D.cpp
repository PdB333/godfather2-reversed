// FUNC_NAME: MathUtils::crossProduct4D
void __thiscall MathUtils::crossProduct4D(float *vecA, float *vecB, float *outVec)
{
  float ax = vecA[0]; // +0x00
  float ay = vecA[1]; // +0x04
  float az = vecA[2]; // +0x08
  float aw = vecA[3]; // +0x0C

  float bx = vecB[0]; // +0x00
  float by = vecB[1]; // +0x04
  float bz = vecB[2]; // +0x08
  float bw = vecB[3]; // +0x0C

  // Compute 3D cross product for the vector components
  outVec[0] = ay * bz - az * by; // +0x00
  outVec[1] = az * bx - ax * bz; // +0x04
  outVec[2] = ax * by - ay * bx; // +0x08
  // The w-component cross product is always zero (aw*bw - aw*bw = 0)
  outVec[3] = aw * bw - aw * bw; // +0x0C

  return;
}