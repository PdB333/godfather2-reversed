// FUNC_NAME: PlayerActionableInfo::getActionableDistanceScale
float __thiscall PlayerActionableInfo::getActionableDistanceScale(int this, int *param_2)
{
  int iVar1;
  float10 fVar2;
  undefined1 local_8 [4];
  float local_4;
  
  FUN_008767c0(this + 0x60, &local_4, local_8); // Get some value from offset +0x60 (likely a base scale or distance)
  iVar1 = *param_2;
  param_2 = (int *)_DAT_00d5780c; // Global pointer, likely to a game manager or settings
  fVar2 = (float10)(**(code **)(iVar1 + 0x1a8))(); // Call virtual function at vtable+0x1a8 on param_2 object (likely getDistance or getRange)
  if ((float10)DAT_00e446c0 < fVar2) { // Compare against a global threshold (likely max distance)
    param_2 = (int *)((DAT_00e446c0 / (float)fVar2) * (DAT_00e446c0 / (float)fVar2)); // Scale factor squared if distance exceeds threshold
  }
  return (float10)(float)param_2 * (float10)local_4; // Multiply base scale by the computed factor
}