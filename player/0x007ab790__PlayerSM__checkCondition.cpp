// FUNC_NAME: PlayerSM::checkCondition
uint __thiscall PlayerSM::checkCondition(int thisPtr, undefined4 param_2, undefined4 param_3, int conditionId, undefined4 param_5)
{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  
  bVar2 = 0;
  switch(conditionId + -10) {
  case 0: // condition 10: check if player is in combat
    return *(uint *)(*(int *)(thisPtr + 0x58) + 0x24a0) >> 1 & 1;
  case 1: // condition 11: check if player is not in conversation
    cVar1 = FUN_0079ebe0(0);
    return (uint)(cVar1 == '\0');
  case 2: // condition 12: check if player can enter combat
    cVar1 = FUN_007f47a0();
    if ((cVar1 == '\0') || (cVar1 = FUN_00481640(), cVar1 != '\0')) {
      cVar1 = FUN_00481640();
      if ((cVar1 != '\0') && (*(char *)(*(int *)(thisPtr + 0x58) + 0x2438) == '\0')) {
        return 1;
      }
    }
    else {
      bVar2 = 1;
      cVar1 = FUN_00690210(0x27);
      if (cVar1 != '\0') {
        return 0;
      }
    }
    break;
  case 3: // condition 13: check if player can exit combat
    bVar2 = 0;
    cVar1 = FUN_00481660();
    if (cVar1 == '\0') {
      cVar1 = FUN_00481640();
      if ((cVar1 != '\0') && (*(char *)(*(int *)(thisPtr + 0x58) + 0x2438) == '\0')) {
        return 1;
      }
    }
    else {
      bVar2 = FUN_007f47a0();
      cVar1 = FUN_00690210(0x27);
      if (cVar1 != '\0') {
        return 0;
      }
    }
    break;
  case 4: // condition 14: check if player has specific weapon
    uVar3 = FUN_006252d0();
    return (uint)((*(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94) & uVar3) != 0);
  case 5: // condition 15: check if player does not have specific weapon
    uVar3 = FUN_006252d0();
    return (uint)((*(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94) & uVar3) == 0);
  case 6: // condition 16: check if player has specific weapon equipped
    cVar1 = *(char *)(*(int *)(thisPtr + 0x58) + 0x1b8c);
    iVar4 = FUN_006252d0();
    return (uint)(iVar4 == cVar1);
  case 7: // condition 17: check if player is in combat or aiming
    cVar1 = FUN_00481660();
    if ((cVar1 == '\0') && (cVar1 = FUN_00481640(), cVar1 == '\0')) {
      return 0;
    }
    return 1;
  case 8: // condition 18: check if player can enter combat and is not in conversation
    if (((*(uint *)(*(int *)(thisPtr + 0x58) + 0x24a0) >> 0xe & 1) != 0) &&
       (cVar1 = FUN_0079ebe0(0), cVar1 == '\0')) {
      FUN_006901e0(0x2e);
      return 1;
    }
    break;
  default:
    bVar2 = FUN_004ac640(param_2,param_3,conditionId,param_5);
  }
  return (uint)bVar2;
}