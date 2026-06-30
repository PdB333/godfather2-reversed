// FUNC_NAME: CarController::applyComplexScale
void __fastcall CarController::applyComplexScale(float *outVector, float *inVector, int carDataPtr)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  iVar1 = *(int *)(carDataPtr + 0x18); // +0x18: pointer to car physics data
  // Dot product of inVector with car's rotation axes (likely forward/right/up) stored at +0x1a0, +0x1a4, +0x1a8
  fVar2 = *(float *)(iVar1 + 0x1a4) * inVector[1] + *(float *)(iVar1 + 0x1a8) * inVector[2] +
          *inVector * *(float *)(iVar1 + 0x1a0);
  // Scale each component by the dot product and a global scale factor (DAT_00e2cd14, likely gPhysicsScale or similar)
  fVar4 = inVector[1] * fVar2 * DAT_00e2cd14;
  fVar5 = inVector[2] * fVar2 * DAT_00e2cd14;
  fVar3 = inVector[3] * fVar2 * DAT_00e2cd14;
  *outVector = *inVector * fVar2 * DAT_00e2cd14;
  outVector[1] = fVar4;
  outVector[2] = fVar5;
  outVector[3] = fVar3;
  return;
}