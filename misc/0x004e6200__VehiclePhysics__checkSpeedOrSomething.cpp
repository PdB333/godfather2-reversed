// FUNC_NAME: VehiclePhysics::checkSpeedOrSomething
void __fastcall VehiclePhysics::checkSpeedOrSomething(int this, int param2)
{
  int iVar1;
  float fVar2;
  
  iVar1 = *(int *)(*(int *)(param2 + 4) + 0x10) + 0x30 + *(short *)(param2 + 0xe) * 0x24;
  fVar2 = (*(float *)(*(int *)(param2 + 4) + 0x8c) - *(float *)(iVar1 + 0x20)) *
          *(float *)(iVar1 + 0x1c);
  if (fVar2 <= 0.0) {
    return;
  }
  if (fVar2 < DAT_00e2b1a4) {
    return;
  }
  return;
}