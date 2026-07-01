// FUNC_NAME: PlayerActionableTargetSM::canPerformAction
undefined1 __thiscall PlayerActionableTargetSM::canPerformAction(int this, int param_2, undefined4 param_3, undefined4 actionType, undefined4 param_5)
{
  float fVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  
  uVar4 = false;
  switch(actionType) {
  case 0x13: // ACTION_TYPE_19 (e.g., extort)
    fVar1 = (float)param_2;
    if (param_2 < 0) {
      fVar1 = fVar1 + DAT_00e44578;
    }
    if (*(float *)(this + 0x74) < fVar1 * DAT_00d5efb8) {
      return true;
    }
    uVar4 = 0;
    iVar6 = FUN_007ab710(); // getPlayer
    if ((iVar6 != 0) && (*(int *)(this + 0x58) != 0)) {
      piVar5 = (int *)FUN_006bc8d0(iVar6,0x369ac561); // getComponent
      if (piVar5 == (int *)0x0) {
        return false;
      }
      cVar3 = (**(code **)(*piVar5 + 0x310))(*(undefined4 *)(this + 0x58)); // isInCombat?
      if (cVar3 != '\0') {
        return false;
      }
      return true;
    }
    break;
  case 0x14: // ACTION_TYPE_20 (e.g., talk)
    iVar6 = *(int *)(*(int *)(this + 0x58) + 0xff0); // target entity type
    if ((iVar6 == 0) || (iVar6 == 0x48)) goto LAB_007ae2f6;
    uVar7 = FUN_00798f50(0x21); // getInputState
    cVar3 = FUN_0079e920(uVar7); // isButtonDown
    if (cVar3 == '\0') goto LAB_007ae2f6;
    goto LAB_007ae307;
  case 0x15: // ACTION_TYPE_21 (e.g., car enter)
    iVar6 = *(int *)(*(int *)(this + 0x58) + 0xff0);
    if ((iVar6 != 0) && (iVar6 != 0x48)) {
      uVar7 = FUN_00798f50(0x22); // getInputState
      cVar3 = FUN_0079e920(uVar7); // isButtonDown
      if (cVar3 != '\0') {
        iVar6 = *(int *)(*(int *)(this + 0x58) + 0xff0);
        if (iVar6 == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = iVar6 + -0x48;
        }
        if (*(char *)(iVar6 + 0x1b8c) == '\x01') {
          return true;
        }
      }
    }
    break;
  case 0x16: // ACTION_TYPE_22 (e.g., attack)
    iVar6 = FUN_007ab710(); // getPlayer
    if (iVar6 == 0) {
      return false;
    }
    uVar7 = FUN_00798f50(0x1e); // getInputState
    cVar3 = FUN_0079e920(uVar7); // isButtonDown
    if (cVar3 != '\0') {
      uVar7 = FUN_00798f50(0x1f); // getInputState
      cVar3 = FUN_0079e920(uVar7); // isButtonDown
      if (cVar3 != '\0') {
        if (*(char *)(iVar6 + 0x1b8c) != '\0') {
          return false;
        }
        return true;
      }
    }
    if (*(char *)(iVar6 + 0x1b8c) != '\0') {
      return false;
    }
    goto LAB_007ae3e6;
  case 0x17: // ACTION_TYPE_23 (e.g., interact)
    iVar6 = FUN_007ab710(); // getPlayer
    if (iVar6 == 0) {
      return false;
    }
    uVar7 = FUN_00798f50(0x1e); // getInputState
    cVar3 = FUN_0079e920(uVar7); // isButtonDown
    if (cVar3 != '\0') {
      return false;
    }
    uVar7 = FUN_00798f50(0x1f); // getInputState
    cVar3 = FUN_0079e920(uVar7); // isButtonDown
    if (cVar3 != '\0') {
      return false;
    }
    uVar7 = FUN_00798f50(0x21); // getInputState
    cVar3 = FUN_0079e920(uVar7); // isButtonDown
    if (cVar3 != '\0') {
      return false;
    }
LAB_007ae2f6:
    uVar4 = true;
    goto LAB_007ae2f8;
  case 0x18: // ACTION_TYPE_24 (e.g., steal car)
    iVar6 = FUN_007ab710(); // getPlayer
    if ((iVar6 != 0) && (*(char *)(iVar6 + 0x1b8c) == '\0')) {
      uVar7 = FUN_00798f50(0x42); // getInputState
      cVar3 = FUN_0079e920(uVar7); // isButtonDown
      if ((cVar3 != '\0') && (cVar3 = FUN_00799b10(), cVar3 != '\0')) {
        uVar4 = (*(byte *)(*(int *)(this + 0x58) + 0x2748) & 0x40) == 0x40;
      }
    }
LAB_007ae3e6:
    cVar3 = FUN_00481660(); // isPlayerInVehicle?
    if ((cVar3 != '\0') || (cVar3 = FUN_00481640(), cVar3 != '\0')) {
      return true;
    }
    break;
  case 0x19: // ACTION_TYPE_25 (e.g., compare family)
    iVar6 = *(int *)(*(int *)(this + 0x58) + 0xff0);
    uVar4 = 0;
    if ((iVar6 != 0) && (uVar4 = 0, iVar6 != 0x48)) {
      iVar6 = *(int *)(*(int *)(this + 0x58) + 0xff0);
      if (iVar6 == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = iVar6 + -0x48;
      }
      cVar3 = *(char *)(iVar6 + 0x1b8c);
      cVar2 = FUN_006252d0(); // getCurrentFamily
      return cVar2 == cVar3;
    }
    break;
  case 0x1a: // ACTION_TYPE_26 (e.g., intimidate)
    iVar6 = FUN_007ab710(); // getPlayer
    if ((iVar6 != 0) && (*(char *)(iVar6 + 0x1b8c) == '\0')) {
      uVar7 = FUN_00798f50(0x1e); // getInputState
      cVar3 = FUN_0079e920(uVar7); // isButtonDown
      if (cVar3 == '\0') {
        uVar7 = FUN_00798f50(0x1f); // getInputState
        cVar3 = FUN_0079e920(uVar7); // isButtonDown
        if (cVar3 == '\0') goto LAB_007ae2f6;
      }
    }
LAB_007ae2f8:
    cVar3 = FUN_00481660(); // isPlayerInVehicle?
    if (cVar3 == '\0') {
LAB_007ae307:
      cVar3 = FUN_00481640(); // isPlayerInCombat?
      if (cVar3 == '\0') {
        return (bool)uVar4;
      }
    }
    return false;
  default:
    uVar4 = FUN_007ab790(param_2,param_3,actionType,param_5); // default handler
  }
  return uVar4;
}