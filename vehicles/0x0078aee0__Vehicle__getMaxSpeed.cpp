// FUNC_NAME: Vehicle::getMaxSpeed
float __fastcall Vehicle::getMaxSpeed(int this)
{
  float fVar1;
  float local_4;

  local_4 = *(float *)(this + 0x58); // +0x58: maxSpeed (base value)
  if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
    fVar1 = (*(float *)(this + 0x54) + local_4) * _DAT_00d5c458; // +0x54: speedModifier, _DAT_00d5c458: globalSpeedMultiplier
    local_4 = (local_4 - fVar1) + fVar1;
    if (DAT_00d5e288 < local_4) {
      local_4 = DAT_00d5e288; // _DAT_00d5e288: maxSpeedCap
    }
  }
  return (float10)local_4;
}