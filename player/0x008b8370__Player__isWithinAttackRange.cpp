// FUNC_NAME: Player::isWithinAttackRange
undefined4 Player::isWithinAttackRange(void)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
  iVar2 = FUN_00471610(); // likely getPlayerPosition or getPlayerTransform
  fVar1 = *(float *)(iVar2 + 0x14); // +0x14 = z position
  iVar2 = FUN_00471610();
  fVar3 = *(float *)(iVar2 + 0x10) * _DAT_00d577a0; // +0x10 = y position, scaled by some factor
  iVar2 = FUN_00471610();
  if (*(float *)(iVar2 + 0x18) * _DAT_00d577a0 + fVar3 + fVar1 < DAT_00d75cb4) { // +0x18 = x position, scaled; compare to threshold
    return 1;
  }
  return 0;
}