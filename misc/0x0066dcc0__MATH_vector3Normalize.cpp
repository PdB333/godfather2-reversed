// FUNC_NAME: MATH_vector3Normalize
void __fastcall MATH_vector3Normalize(float *outVec)
{
  float fVar1;
  float *inVec;
  float sqrLen;
  
  fVar1 = *inVec;
  sqrLen = fVar1 * fVar1 + inVec[1] * inVec[1] + inVec[2] * inVec[2];
  
  // Check for zero length using epsilon threshold
  if (sqrLen <= DAT_00e2cbe0) { // +0x0: epsilon threshold (close to zero)
    sqrLen = 0.0;               // Return zero vector if input is degenerate
  }
  else {
    sqrLen = DAT_00e2b1a4 / SQRT(sqrLen); // +0x0: inverse length scale factor
  }
  
  *outVec = fVar1 * sqrLen;
  outVec[1] = sqrLen * inVec[1];
  outVec[2] = sqrLen * inVec[2];
  return;
}