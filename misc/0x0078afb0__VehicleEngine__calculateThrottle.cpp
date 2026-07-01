// FUNC_NAME: VehicleEngine::calculateThrottle
int __fastcall VehicleEngine::calculateThrottle(int this)
{
  int iVar1;
  uint3 uVar2;
  float fVar3;
  
  iVar1 = **(int **)(DAT_012233a0 + 4);
  fVar3 = *(float *)(this + 0x54); // +0x54: currentRPM
  if (((iVar1 != 0) && (iVar1 = iVar1 + -0x1f30, iVar1 != 0)) &&
     (fVar3 = (fVar3 + *(float *)(this + 0x58)) * _DAT_00d5c458, // +0x58: maxRPM
     fVar3 = fVar3 - (*(float *)(this + 0x58) - fVar3), fVar3 < 0.0)) {
    fVar3 = 0.0;
  }
  uVar