// FUNC_NAME: Player::updateAimAssist
void __thiscall Player::updateAimAssist(int this, float param_2, undefined4 *outParam3, undefined4 *outParam4, undefined1 *outParam5)
{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined1 local_1c [24];
  
  iVar2 = FUN_00471610(); // Get player camera position
  fVar6 = *(float *)(this + 0x1014) - *(float *)(iVar2 + 0x38); // deltaZ
  fVar5 = *(float *)(this + 0x1010) - *(float *)(iVar2 + 0x34); // deltaY
  fVar4 = *(float *)(this + 0x100c) - *(float *)(iVar2 + 0x30); // deltaX
  fVar4 = SQRT(fVar6 * fVar6 + fVar5 * fVar5 + fVar4 * fVar4); // distance to target
  
  FUN_008750c0(local_1c); // Get forward direction vector
  iVar2 = FUN_00471610(); // Get player camera position again
  fVar3 = (float10)FUN_004a0b00(iVar2 + 0x30, local_1c, this + 0x100c, &DAT_00d75690); // Dot product check
  uVar1 = _DAT_00d5780c; // Some global state
  
  if (fVar3 < (float10)0) {
    // Target is behind player
    if (fVar4 <= DAT_00d5eee4) { // Within close range
      *outParam3 = 0;
      *outParam4 = uVar1;
      *outParam5 = 1;
    }
  }
  else {
    // Target is in front of player
    FUN_0085fa40(outParam3, outParam4, outParam5, fVar4, 0x3f800000); // Apply aim assist
  }
  
  param_2 = *(float *)(this + 0x1018) - param_2; // Update some timer
  *(float *)(this + 0x1018) = param_2;
  if (param_2 < 0.0) {
    *(undefined4 *)(this + 0x1018) = 0;
  }
  
  return;
}