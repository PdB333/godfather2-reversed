// FUNC_NAME: CameraManager::getCameraPositionOrSomething
void __thiscall CameraManager::getCameraPositionOrSomething(int thisPtr, float *outPos)
{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  
  outPos[0] = *(float *)(thisPtr + 0x1050);
  outPos[1] = *(float *)(thisPtr + 0x1054);
  outPos[2] = *(float *)(thisPtr + 0x1058);
  fVar1 = *(float *)(thisPtr + 0xfc4);
  fVar2 = *(float *)(thisPtr + 0x1148);
  if (fVar1 != _DAT_00d577a0) {
    dVar3 = (double)fVar2;
    FUN_00b99e20();
    dVar4 = (double)fVar2;
    outPos[0] = outPos[0] - (float)dVar3 * fVar1;
    FUN_00b99fcb();
    outPos[2] = (float)dVar4 * fVar1 + outPos[2];
  }
  return;
}