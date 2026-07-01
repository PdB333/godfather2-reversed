// FUNC_NAME: PlayerSM::canTransitionToState
undefined1 __thiscall PlayerSM::canTransitionToState(int this, uint stateIndex, undefined4 param3, undefined4 param4, undefined4 param5)
{
  uint flags;
  bool bVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte local_4;
  bool local_3;
  
  iVar8 = *(int *)(this + 0x58); // +0x58: playerData pointer
  iVar7 = FUN_007e56b0(iVar8); // getPlayerMovementState
  if ((iVar7 == 2) && (*(uint *)(this + 0x274) < stateIndex)) { // +0x274: lastStateIndex
    local_4 = 1; // isRecentState
LAB_007e5d49:
    local_3 = false; // isCooldownExpired
  }
  else {
    local_4 = 0;
    local_3 = true; // cooldown expired
    if (stateIndex <= (uint)(*(int *)(this + 0x278) + DAT_00e5341c)) goto LAB_007e5d49; // +0x278: cooldownTimer
  }
  if ((*(uint *)(iVar8 + 0x8e4) >> 7 & 1) == 0) { // playerFlags & IS_DEAD
    if ((*(uint *)(iVar8 + 0x8e0) >> 10 & 1) != 0) { // playerFlags & IS_IN_COVER
      iVar9 = *(int *)(iVar8 + 0x74c); // coverState pointer
      goto LAB_007e5d78;
    }
LAB_007e5d91:
    bVar2 = false; // isInCoverWithProperState
  }
  else {
    iVar9 = *(int *)(iVar8 + 0x24b4); // ragdollState pointer
LAB_007e5d78:
    if (((iVar9 == 0) || (iVar9 == 0x48)) || (bVar2 = true, *(char *)(iVar9 + 0x165) != '\x18'))
    goto LAB_007e5d91;
  }
  if ((iVar7 == 0) || (bVar2)) { // isStanding or in cover
    bVar3 = false;
  }
  else {
    bVar3 = true; // isMoving
  }
  flags = *(uint *)(iVar8 + 0x8e0); // playerFlags bitfield +0x8e0
  bVar5 = (byte)(flags >> 0x19) & 1; // IS_STUNNED flag
  switch(param4) {
  case 0x13: // STATE_JUMP
    iVar8 = FUN_007ab150(); // getGameplayManager
    if ((*(byte *)(iVar8 + 4) & 1) == 0) {
      return true;
    }
    iVar8 = FUN_007ab160(); // getGameplayManager2
    if ((*(byte *)(iVar8 + 4) & 8) == 0) {
      return true;
    }
    bVar5 = FUN_007f47a0(); // isPlayerInVehicle
    goto LAB_007e5e00;
  case 0x14: // STATE_FALL
    iVar8 = FUN_007ab150();
    if ((((*(byte *)(iVar8 + 4) & 1) != 0) &&
        (iVar8 = FUN_007ab160(), (*(byte *)(iVar8 + 4) & 8) != 0)) &&
       (cVar4 = FUN_007f47a0(), cVar4 == '\0')) {
      return true;
    }
    break;
  case 0x15: // STATE_MELEE_ATTACK
    uVar6 = FUN_007e5730(stateIndex); // isMeleeStateAvailable
    return uVar6;
  case 0x16: // STATE_MELEE_ATTACK_CANCEL
    cVar4 = FUN_007e5730(stateIndex);
    return cVar4 == '\0';
  case 0x17: // STATE_MOVE_FORWARD
    if (!bVar3) {
      return false;
    }
    if ((flags & 0x1000000) == 0) { // IS_IN_COMBAT
      return true;
    }
    goto LAB_007e5e00;
  case 0x18: // STATE_STAND
    return !bVar3;
  case 0x19: // STATE_COVER_ENTER
    if (((local_4 != 0) && (!bVar2)) &&
       ((*(char *)(this + 0x27d) != '\0' && // isCoverActionsEnabled
        ((cVar4 = FUN_00481620(), cVar4 != '\0' && (cVar4 = FUN_00481660(), cVar4 == '\0')))))) {
      return true;
    }
    break;
  case 0x1a: // STATE_COVER_EXIT
    if (local_4 == 0) {
      return false;
    }
    if ((flags & 0x1000000) != 0) goto LAB_007e5e97;
    goto LAB_007e5e99;
  case 0x1b: // STATE_INTERACT
  case 0x1e: // STATE_USE_ITEM
    return local_3;
  case 0x1c: // STATE_OPEN_DOOR
    iVar8 = FUN_006d6ac0(); // isNearbyDoor
    if ((iVar8 == 0) && (!bVar2)) {
      return true;
    }
    break;
  case 0x1d: // STATE_GRAPPLE
    cVar4 = FUN_00690210(0x44); // checkButtonPressed
    if ((((cVar4 != '\0') || ((local_4 != 0 && (bVar2)))) &&
        (cVar4 = FUN_00690150(0x27), cVar4 == '\0')) && // !isInputBlocked
       ((cVar4 = FUN_00690150(0x26), cVar4 == '\0' && (((flags & 0x1000000) == 0 || (bVar5 != 0))))))
       {
      cVar4 = FUN_00690150(0x29); // isInputBlocked2
      if (cVar4 == '\0') {
        return true;
      }
      cVar4 = FUN_00481620(); // isPlayerAbleToGrapple
      if ((cVar4 != '\0') && (cVar4 = FUN_00481660(), cVar4 == '\0')) {
        return true;
      }
    }
    break;
  case 0x1f: // STATE_CROUCH
    bVar5 = local_4;
LAB_007e5e97:
    if (bVar5 == 0) {
      return false;
    }
LAB_007e5e99:
    if (((!bVar2) && (cVar4 = FUN_00481620(), cVar4 != '\0')) &&
       (cVar4 = FUN_00481660(), cVar4 == '\0')) {
      return true;
    }
    break;
  case 0x20: // STATE_STAND_UP
    cVar4 = FUN_00481660(); // isPlayerCrouching
    if ((cVar4 != '\0') && (!bVar2)) {
      return true;
    }
    break;
  case 0x21: // STATE_STUNNED
    cVar4 = FUN_00481660();
    if (cVar4 == '\0') {
      return false;
    }
    bVar5 = FUN_00690150(0x29);
LAB_007e5e00:
    if (bVar5 != 0) {
      return true;
    }
    break;
  case 0x22: // STATE_TAKE_DAMAGE
    uVar6 = FUN_00690150(0x29);
    return uVar6;
  default:
    uVar6 = FUN_007ab790(stateIndex, param3, param4, param5); // defaultStateTransitionCheck
    return uVar6;
  }
  return false;
}