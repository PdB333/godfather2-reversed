// FUNC_NAME: MathUtils::normalizeVector3D
void __fastcall MathUtils::normalizeVector3D(float *outVec)
{
  float fVar1;
  float *in_EAX;
  float fVar2;
  
  fVar1 = *in_EAX;
  fVar2 = fVar1 * fVar1 + in_EAX[1] * in_EAX[1] + in_EAX[2] * in_EAX[2];
  if (fVar2 <= DAT_00e2cbe0) { // epsilon threshold (likely 0.0f or very small)
    fVar2 = 0.0;
  }
  else {
    fVar2 = DAT_00e2b1a4 / SQRT(fVar2); // DAT_00e2b1a4 is 1.0f (inverse sqrt factor)
  }
  *outVec = fVar1 * fVar2;
  outVec[1] = fVar2 * in_EAX[1];
  outVec[2] = fVar2 * in_EAX[2];
  return;
}