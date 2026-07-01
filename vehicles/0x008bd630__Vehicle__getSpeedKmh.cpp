// FUNC_NAME: Vehicle::getSpeedKmh
float __fastcall Vehicle::getSpeedKmh(int this)
{
  int iVar1;
  float fVar2;
  
  if (*(float *)(DAT_0112f938 + 4) != 0.0) {
    iVar1 = FUN_006b1a20(); // likely getGameTickDelta or similar
    fVar2 = (float)iVar1;
    if (iVar1 < 0) {
      fVar2 = fVar2 + (float)DAT_00e44578; // 0x100000000 as float for unsigned conversion
    }
    return ((float)*(float *)(*(int *)(this + 0x1d0) + 0x10) / // +0x1d0: vehicle physics data ptr, +0x10: speed magnitude
           (float)*(float *)(DAT_0112f938 + 4)) * fVar2; // DAT_0112f938+4: some time scale factor
  }
  return 0.0f;
}