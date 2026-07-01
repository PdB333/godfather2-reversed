// FUNC_NAME: ChaseCamera::updateLookAhead
void ChaseCamera::updateLookAhead(int *this, int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00471610(); // likely getPlayerVehicle or getTargetObject
  (**(code **)(*this + 0x48))(param_2); // call virtual function at vtable+0x48 (e.g., base update)
  if (_DAT_00d5c458 < *(float *)(param_2 + 4) - *(float *)(iVar1 + 0x34)) {
    *(float *)(param_2 + 4) = *(float *)(iVar1 + 0x34) + _DAT_00d5c458;
  }
  return;
}