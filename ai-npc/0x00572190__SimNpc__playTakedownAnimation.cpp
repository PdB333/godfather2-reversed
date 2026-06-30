// FUNC_NAME: SimNpc::playTakedownAnimation
undefined1 __thiscall SimNpc::playTakedownAnimation(int thisPtr, int animControllerIndex, char param_3, undefined4 param_4, undefined1 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9, undefined4 param_10)
{
  float fVar1;
  int iVar2;
  float fVar3;
  int in_EAX;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  undefined1 local_65;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_34;
  undefined4 local_2c;
  undefined4 *local_20;
  
  local_65 = 0;
  if ((in_EAX == 0) || (animControllerIndex < 0)) {
    return 0;
  }
  iVar6 = *(int *)(in_EAX + 0x124); // AnimatorController +0x124
  iVar4 = 0;
  if (0 < animControllerIndex) {
    do {
      iVar6 = *(int *)(iVar6 + 0x124); // Follow linked list
      if (iVar6 == 0) {
        return 0;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < animControllerIndex);
  }
  if (iVar6 == 0) {
    return 0;
  }
  if (param_2 != -1) {
    local_65 = 1;
    if (*(int *)(iVar6 + 0x10c) != 0) { // Current animation state
      FUN_005826b0(*(int *)(iVar6 + 0x10c), iVar6, param_6); // Stop current animation
    }
    local_60 = 0; // Initialize animation params
    local_54 = param_10;
    local_5c = param_8;
    local_58 = param_9;
    FUN_00586970(); // Get current time
    iVar4 = *(int *)(iVar6 + 0x14); // Animation time
    local_20 = &local_60;
    local_34 = param_2; // Anim index
    local_2c = param_7; // Blend time
    FUN_00578770(); // Start animation
    *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xffffff7f; // Clear some flag
    *(undefined1 *)(iVar6 + 0x120) = param_5; // Set loop flag
    fVar8 = DAT_00e2b1a4;
    if (param_3 != '\0') {
      iVar2 = *(int *)(iVar6 + 0x110); // Previous param
      fVar1 = *(float *)(iVar6 + 0x114); // Previous anim speed
      *(undefined4 *)(iVar6 + 0x110) = 1;
      *(undefined1 *)(iVar6 + 0x121) = 0;
      fVar3 = DAT_00e2cb90;
      if (*(int *)(iVar6 + 0x2f0) == 0) { // No override speed
        fVar7 = ((*(float *)(iVar6 + 0x24) - fVar8) / _DAT_011260b0) * DAT_00e35654;
        *(float *)(iVar6 + 0x118) = fVar7; // Animation speed
        if (fVar3 < fVar7) {
          *(float *)(iVar6 + 0x118) = fVar3; // Cap speed
        }
        *(undefined4 *)(iVar6 + 0x11c) = 0; // Clear extra param
      }
      else {
        iVar5 = FUN_00571d70(); // Get new speed from somewhere
        fVar8 = DAT_00e2b1a4;
        *(float *)(iVar6 + 0x118) = *(float *)(iVar5 + 4) / _DAT_011260b0;
        *(undefined4 *)(iVar6 + 0x11c) = *(undefined4 *)(iVar5 + 0xc);
      }
      if (iVar2 != 0) { // If was playing something before
        if (iVar2 < 0) {
          fVar8 = (fVar8 - fVar1 * _DAT_00e446b8) * *(float *)(iVar6 + 0x118);
          *(float *)(iVar6 + 0x114) = fVar8;
          if (fVar8 < 0.0) {
            *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xedfffffe;
            *(undefined4 *)(iVar6 + 0x114) = 0;
            return 1;
          }
          goto LAB_00572344;
        }
LAB_00572397:
        *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xedfffffe;
        *(undefined4 *)(iVar6 + 0x114) = 0;
        return 1;
      }
      if (iVar4 == -1) goto LAB_00572397;
    }
    *(undefined4 *)(iVar6 + 0x110) = 0;
  }
LAB_00572344:
  *(uint *)(iVar6 + 0x10) = *(uint *)(iVar6 + 0x10) & 0xedfffffe;
  return local_65;
}