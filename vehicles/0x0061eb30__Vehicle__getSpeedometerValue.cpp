// FUNC_NAME: Vehicle::getSpeedometerValue
undefined4 __fastcall Vehicle::getSpeedometerValue(int this)
{
  float fVar1;
  int iVar2;
  undefined4 result;
  
  result = 0;
  if (*(int *)(this + 0x98) != 0) {
    fVar1 = *(float *)(*(int *)(this + 0x98) + 0x1c8); // +0x1c8: maxSpeed (float)
    if (DAT_00e2b05c < fVar1) { // global min speed threshold
      iVar2 = FUN_00d01890(); // likely getCurrentSpeed()
      result = (undefined4)(longlong)ROUND((1.0 / fVar1) * (float)iVar2 * DAT_00e2e230); // scale to 0-100 or similar
    }
  }
  return result;
}