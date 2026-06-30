// FUNC_NAME: MathUtils::normalizeVector3
void __fastcall normalizeVector3(float *outResult, float *inVector)
{
  float lengthSq;
  float invLength;
  
  lengthSq = inVector[0] * inVector[0] + inVector[1] * inVector[1] + inVector[2] * inVector[2];
  if (lengthSq <= 0.0f) { // DAT_00e2cbe0 is likely 0.0f (epsilon check)
    invLength = 0.0f;
  }
  else {
    invLength = 1.0f / SQRT(lengthSq); // DAT_00e2b1a4 is 1.0f
  }
  outResult[0] = inVector[0] * invLength;
  outResult[1] = inVector[1] * invLength;
  outResult[2] = inVector[2] * invLength;
}