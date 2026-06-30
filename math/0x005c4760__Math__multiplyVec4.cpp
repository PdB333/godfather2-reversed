// FUNC_NAME: Math::multiplyVec4
void __thiscall Math::multiplyVec4(float *inVecA, float *inVecB, float *outVec)
{
  float x1;
  float y1;
  float z1;
  float w1;
  float x2;
  float y2;
  float z2;
  float w2;
  float *inVecA_reg;
  
  // inVecA is passed via EAX (this pointer convention)
  inVecA_reg = inVecA;
  
  // Load components from first vector
  x1 = inVecA_reg[1];  // +0x04
  y1 = inVecA_reg[2];  // +0x08
  z1 = inVecA_reg[3];  // +0x0C
  w1 = inVecA_reg[0];  // +0x00
  
  // Load components from second vector
  x2 = inVecB[1];  // +0x04
  y2 = inVecB[2];  // +0x08
  z2 = inVecB[3];  // +0x0C
  w2 = inVecB[0];  // +0x00
  
  // Perform component-wise multiplication
  outVec[0] = w1 * w2;  // +0x00
  outVec[1] = x1 * x2;  // +0x04
  outVec[2] = y1 * y2;  // +0x08
  outVec[3] = z1 * z2;  // +0x0C
  
  return;
}