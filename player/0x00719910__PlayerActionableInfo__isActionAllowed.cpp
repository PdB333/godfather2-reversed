// FUNC_NAME: PlayerActionableInfo::isActionAllowed
undefined1 __thiscall PlayerActionableInfo::isActionAllowed(int thisPtr)
{
  uint uVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  undefined1 result;

  result = 0;
  // +0x338: pointer to target entity (e.g., vehicle)
  if (*(int *)(thisPtr + 0x338) == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)(thisPtr + 0x338) - 0x48;  // adjust to base of target object
  }
  bVar2 = true;
  // +0x18: pointer to player entity
  // vtable offset 0x1bc: likely isPlayerAlive()
  cVar3 = (*(code (__thiscall)**(int))(*(int *)(thisPtr + 0x18) + 0x1bc))(*(int *)(thisPtr + 0x18));
  if (((cVar3 != '\0') &&
       (*(int *)(thisPtr + 0x18) != 0)) &&
      (iVar4 = FUN_0043b870(DAT_01131040), iVar4 != 0) &&
      ((*(int *)(iVar4 + 0x1c) != 0 && (*(int *)(iVar4 + 0x1c) != 0x48)))) {
    // FUN_009b1540: probably canEnterVehicle() based on context
    result = FUN_009b1540();
    bVar2 = false;
  }
  // bit 9 at player entity offset +0x8ec: e.g., "isDead" flag
  if ((*(uint *)(*(int *)(thisPtr + 0x18) + 0x8ec) >> 9 & 1) != 0) {
    return 0;
  }
  // bit 12 at player entity offset +0x1f54: e.g., "isOnLadder" or similar state
  if (((*(uint *)(*(int *)(thisPtr + 0x18) + 0x1f54) >> 12 & 1) != 0) &&
      (cVar3 = FUN_0072d880(), cVar3 != '\0')) {
    return 1;
  }
  if ((bVar2) && (iVar5 != 0)) {
    // vtable offset 0xbc: likely getTargetDistance() or canInteractWith()
    fVar6 = (float10)(*(code (__thiscall)**(int))(*(int *)(thisPtr + 0x18) + 0xbc))(iVar5);
    if (fVar6 == (float10)0) {
      return result;
    }
    uVar1 = *(uint *)(thisPtr + 0x308);  // +0x308: action flags
    iVar5 = FUN_007ff880();  // e.g., getGameplayManager()
    if (((iVar5 == 0) || (*(int *)(iVar5 + 0xb74) == 0)) &&
        ((cVar3 = FUN_007f7c60(), cVar3 == '\0' ||
          (cVar3 = FUN_00716d40(), cVar3 != '\0')))) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    // bit 3 in flags: e.g., "actionBlockedByVehicle"
    if (((uVar1 >> 3 & 1) != 0) && (cVar3 = FUN_007181c0(), cVar3 != '\0')) {
      return 0;
    }
    cVar3 = FUN_0072d880();
    if (((cVar3 != '\0') || (!bVar2)) && (cVar3 = FUN_007182b0(), cVar3 == '\0')) {
      return 1;
    }
    return 0;
  }
  return result;
}