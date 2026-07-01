// FUNC_NAME: PlayerActionableTargetSM::updateTargetSelection
char __thiscall PlayerActionableTargetSM::updateTargetSelection(int thisPtr, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, int param_6, undefined4 param_7)
{
  char cVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 local_34;
  undefined4 local_30;
  int local_c[3];
  
  // Check if target is already selected or if there's a pending target selection
  if ((*(int *)(thisPtr + 0x44) != 0) ||
     ((*(int *)(thisPtr + 0x4c) != 0 && (*(char *)(thisPtr + 0x48) == '\0')))) {
    FUN_008eb960(param_3, param_4, param_6, param_7);
    return '\x01';
  }
  
  // If no specific target index, get current target
  if (param_6 == -1) {
    param_6 = FUN_008e9ae0(param_5);
  }
  
  iVar3 = FUN_0045d9e0(param_5);
  piVar4 = (int *)FUN_008e9a40(param_5);
  
  // Check if target is valid and not already being targeted
  if (((piVar4 != (int *)0x0) &&
      ((((*piVar4 != 0 || (piVar4[1] != 0)) || (piVar4[2] != 0)) || (piVar4[3] != 0)))) &&
     ((iVar3 != 0 && (cVar1 = FUN_004209a0(), cVar1 == '\0')))) {
    FUN_00401f40(iVar3);
    iVar3 = FUN_008ecbc0(local_34);
    local_30 = DAT_0122337c;
    uVar5 = FUN_004059b0(local_34);
    iVar6 = FUN_00402610(uVar5);
    
    // Check if target is in range or if we can acquire it
    if (((iVar6 == 3) || (cVar1 = FUN_008e9a10(param_4), cVar1 != '\0')) &&
       ((iVar3 != 0 && (*(int *)(iVar3 + 8) < 3)))) {
      cVar1 = FUN_008ef8a0(param_6, 0);
      if (cVar1 == '\0') {
        return '\0';
      }
      uVar5 = FUN_008ebf00(param_2, param_5, param_4, param_7);
      FUN_008eb6b0(uVar5, param_6);
      *(undefined4 *)(iVar3 + 8) = 2;
      return cVar1;
    }
    
    iVar6 = FUN_008ecd20(local_34);
    if (iVar6 != 0) {
      cVar1 = FUN_008ef8a0(param_6, iVar6);
      if (cVar1 == '\0') {
        return '\0';
      }
      FUN_008ecd20(local_34);
      iVar3 = FUN_009c8e50(0x2c);
      if (iVar3 == 0) {
        uVar5 = 0;
      } else {
        uVar5 = FUN_008eac00(param_3, param_4, param_6, param_7);
      }
      FUN_008eb500(uVar5);
      cVar2 = FUN_008ecce0(local_34);
      if (cVar2 == '\0') {
        return cVar1;
      }
      FUN_008ef500(param_4);
      FUN_004061d0(param_4);
      return cVar1;
    }
    
    cVar1 = FUN_008efbf0(local_34, param_6, 1);
    if (cVar1 != '\0') {
      if (iVar3 == 0) {
        if (*(uint *)(thisPtr + 0x18) <= *(uint *)(thisPtr + 0x14)) {
          FUN_008ef250(&local_34);
          iVar3 = FUN_009c8e50(0x2c);
          if (iVar3 == 0) {
            uVar5 = 0;
          } else {
            uVar5 = FUN_008eac00(param_3, param_4, param_6, param_7);
          }
          FUN_008eb500(uVar5);
          FUN_008ef500(param_4);
          FUN_004061d0(param_4);
          return '\x01';
        }
        uVar5 = FUN_008ef150(&local_34);
        uVar7 = FUN_008eac00(param_3, param_4, param_6, param_7);
        FUN_008ef410(uVar5, local_34, param_4, uVar7);
        if (local_c[0] == 0) {
          return '\x01';
        }
        FUN_004daf90(local_c);
        return '\x01';
      }
      if (*(int *)(iVar3 + 8) == 3) {
        uVar5 = FUN_008ebf00(param_2, param_5, param_4, param_7);
        FUN_008eb6b0(uVar5, param_6);
        *(undefined4 *)(iVar3 + 8) = 2;
        return '\x01';
      }
      if (*(int *)(iVar3 + 8) != 4) {
        return '\x01';
      }
      uVar5 = FUN_008eac00(param_3, param_4, param_6, param_7);
      FUN_008ef410(iVar3, local_34, param_4, uVar5);
      if (local_c[0] == 0) {
        return '\x01';
      }
      FUN_004daf90(local_c);
      return '\x01';
    }
  }
  return '\0';
}