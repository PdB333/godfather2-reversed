// FUNC_NAME: MathUtils::scaleVectorByGlobal
void MathUtils::scaleVectorByGlobal(void)

{
  float *outVector;
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = *(float *)(DAT_012233a4 + 0x44);  // +0x44: x component of some global vector?
  fVar2 = *(float *)(DAT_012233a4 + 0x48);  // +0x48: y component?
  fVar3 = *(float *)(DAT_012233a4 + 0x4c);  // +0x4c: z component?
  *outVector = *(float *)(DAT_012233a4 + 0x40);  // +0x40: source vector's x?
  outVector[1] = fVar1;
  outVector[2] = fVar2;
  outVector[3] = fVar3;
  // DAT_00e2b04c likely is a global scalar multiplier (e.g., time scale or force scale)
  fVar1 = DAT_00e2b04c * outVector[1];
  fVar2 = DAT_00e2b04c * outVector[2];
  fVar3 = DAT_00e2b04c * outVector[3];
  *outVector = DAT_00e2b04c * *outVector;
  outVector[1] = fVar1;
  outVector[2] = fVar2;
  outVector[3] = fVar3;
  return;
}