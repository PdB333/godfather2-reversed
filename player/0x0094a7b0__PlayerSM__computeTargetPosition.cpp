// FUNC_NAME: PlayerSM::computeTargetPosition
undefined1 __thiscall PlayerSM::computeTargetPosition(int this, undefined4 *outPos)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float fVar5;
  
  iVar4 = *(int *)(this + 0x118); // +0x118: state
  if ((((iVar4 == 1) && (*(int *)(this + 0x154) != 0)) && (*(int *)(this + 0x154) != 0x48)) &&
     ((*(uint *)(this + 0x11c) >> 1 & 1) != 0)) {
    uVar3 = FUN_00471610(); // getPlayerPosition
    FUN_0044b4e0(outPos,uVar3); // copyVector3
    return 1;
  }
  if ((((iVar4 == 4) || (iVar4 == 5)) &&
      ((*(int *)(this + 0x15c) != 0 &&
       ((*(int *)(this + 0x15c) != 0x48 && (iVar4 = FUN_00791300(), iVar4 != 0)))))) &&
     ((*(uint *)(this + 0x11c) >> 1 & 1) != 0)) {
    FUN_00791300(); // getTargetPosition
    uVar3 = FUN_00471610(); // getPlayerPosition
    FUN_0044b4e0(outPos,uVar3); // copyVector3
    return 1;
  }
  fVar5 = DAT_00e44564; // globalTime
  uVar3 = _DAT_00d5780c; // zeroVector
  if ((*(uint *)(this + 0x11c) >> 2 & 1) == 0) {
    *outPos = _DAT_00d5780c;
    outPos[1] = 0;
    outPos[2] = 0;
    outPos[3] = 0;
    outPos[4] = 0;
    outPos[5] = uVar3;
    outPos[6] = 0;
    outPos[7] = 0;
    outPos[8] = 0;
    outPos[9] = 0;
    outPos[10] = uVar3;
    outPos[0xb] = 0;
    outPos[0xc] = 0;
    outPos[0xd] = 0;
    outPos[0xe] = 0;
    outPos[0xf] = uVar3;
  }
  else {
    FUN_0056b8a0((DAT_00e44564 - *(float *)(this + 0x120)) * DAT_00e445c8,0,0,outPos); // lerpPosition
    fVar5 = DAT_00e44564;
  }
  switch(*(undefined4 *)(this + 0x118)) {
  case 0:
    uVar3 = *(undefined4 *)(this + 0x134);
    uVar1 = *(undefined4 *)(this + 0x138);
    uVar2 = *(undefined4 *)(this + 0x13c);
    outPos[0xc] = *(undefined4 *)(this + 0x130);
    outPos[0xd] = uVar3;
    outPos[0xe] = uVar1;
    outPos[0xf] = uVar2;
    return 1;
  case 1:
    if (*(int *)(this + 0x154) == 0) {
      return 0;
    }
    if (*(int *)(this + 0x154) == 0x48) {
      return 0;
    }
    break;
  case 2:
    if (*(int *)(this + 0x168) == 0) {
      return 0;
    }
    if (*(int *)(this + 0x168) == 0x48) {
      return 0;
    }
    iVar4 = FUN_00950b20(); // isTargetValid
    if (iVar4 == 0) {
      return 0;
    }
    goto LAB_0094a95a;
  default:
    return 0;
  case 4:
switchD_0094a90f_caseD_4:
    if (*(int *)(this + 0x15c) == 0) {
      return 0;
    }
    if (*(int *)(this + 0x15c) != 0x48) {
      uVar3 = FUN_00790cd0(); // getTargetPosition
      FUN_00424680(outPos + 0xc,uVar3); // copyVector3
      return 1;
    }
    return 0;
  case 5:
    if (((*(int *)(this + 0x15c) == 0) || (*(int *)(this + 0x15c) == 0x48)) ||
       (iVar4 = FUN_00791300(), fVar5 = DAT_00e44564, iVar4 == 0)) {
      if ((*(uint *)(this + 0x11c) >> 0x1d & 1) != 0) {
        FUN_0056b8a0((fVar5 - *(float *)(this + 0x200)) * DAT_00e445c8,0,0,outPos); // lerpPosition
        uVar3 = *(undefined4 *)(this + 500);
        uVar1 = *(undefined4 *)(this + 0x1f8);
        uVar2 = *(undefined4 *)(this + 0x1fc);
        outPos[0xc] = *(undefined4 *)(this + 0x1f0);
        outPos[0xd] = uVar3;
        outPos[0xe] = uVar1;
        outPos[0xf] = uVar2;
        return 1;
      }
      goto switchD_0094a90f_caseD_4;
    }
  }
  iVar4 = FUN_00471610(); // getPlayerPosition
  iVar4 = iVar4 + 0x30;
LAB_0094a95a:
  FUN_00424680(outPos + 0xc,iVar4); // copyVector3
  return 1;
}