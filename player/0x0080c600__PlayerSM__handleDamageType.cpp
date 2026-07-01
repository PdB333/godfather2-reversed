// FUNC_NAME: PlayerSM::handleDamageType
undefined1 __thiscall PlayerSM::handleDamageType(int this, int attacker, undefined4 damageType, int damageAmount, undefined4 param_5)
{
  undefined1 uVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  bool bResult;
  
  if (damageAmount == 10) {
    cVar2 = FUN_007fd640(); // IsPlayerControlled?
    bResult = cVar2 == '\0';
    if ((!bResult) &&
       ((cVar2 = FUN_00481640(), cVar2 != '\0' || (cVar2 = FUN_00481660(), cVar2 != '\0')))) {
      // +0x50 : PlayerStateMachine*, +0xffc : some offset into state data
      iVar4 = *(int *)(*(int *)(this + 0x50) + 0xffc);
      bResult = true;
      if (iVar4 == 0) {
        piVar3 = (int *)0x0;
      }
      else {
        piVar3 = (int *)(iVar4 + -0x48); // Get containing object
      }
      damageAmount = 0;
      // Virtual call on object at piVar3, with interface ID 0x55859efa
      cVar2 = (**(code **)(*piVar3 + 0x10))(0x55859efa, &damageAmount);
      if (((cVar2 != '\0') && (attacker != 0)) && (cVar2 = FUN_007fd640(), cVar2 != '\0')) {
        if (*(int *)(attacker + 0xffc) == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(attacker + 0xffc) + -0x48;
        }
        if (iVar4 == *(int *)(this + 0x50)) {
          bResult = false; // Don't take damage if attacker is self
        }
      }
    }
  }
  else {
    bResult = true;
    if (damageAmount != 0xb) {
      uVar1 = FUN_004ac640(attacker, damageType, damageAmount, param_5); // default damage handling
      return uVar1;
    }
    // +0x50 : PlayerStateMachine*, +0x8e6 : invulnerability flag
    if (((*(byte *)(*(int *)(this + 0x50) + 0x8e6) & 1) != 0) ||
       (*(float *)(this + 0x30) <= _DAT_00d577a0)) {
      return false;
    }
  }
  return bResult;
}