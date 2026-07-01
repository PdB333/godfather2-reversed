// FUNC_NAME: SomeClass::getOrCreateSomething
undefined4 * __thiscall SomeClass::getOrCreateSomething(int this, undefined4 *outParam, undefined4 param3)
{
  undefined ***pppuVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined ***pppuVar5;
  undefined *local_80[19];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Check if count at +0xc is non-zero
  if (*(int *)(this + 0xc) != 0) {
    // If count is exactly 1, use the first element directly
    if (*(int *)(this + 0xc) == 1) {
      pppuVar5 = (undefined ***)**(int **)(this + 8);
    }
    else {
      // Look up index for param3
      uVar3 = FUN_0082c2c0(param3);
      if (uVar3 == 0xffffffff) {
        // Not found - use default/fallback data
        FUN_008334a0();
        local_34 = _DAT_00d5780c;
        local_30 = _DAT_00d5780c;
        local_2c = 0;
        local_80[0] = &PTR_LAB_00d736c0;
        local_20 = _DAT_00d735f0;
        uStack_1c = _UNK_00d735f4;
        uStack_18 = _UNK_00d735f8;
        uStack_14 = _UNK_00d735fc;
        pppuVar5 = local_80;
      }
      else {
        // Store the index at +0x4
        *(uint *)(this + 4) = uVar3;
        // Determine next index (wrap around)
        if (uVar3 < *(int *)(this + 0xc) - 1U) {
          iVar4 = uVar3 + 1;
        }
        else {
          iVar4 = 0;
        }
        // Get pointer to current and next element from array at +0x8
        pppuVar5 = *(undefined ****)(*(int *)(this + 8) + iVar4 * 4);
        pppuVar1 = *(undefined ****)(*(int *)(this + 8) + uVar3 * 4);
        // Check if next element is valid
        cVar2 = FUN_00835a00(param3, pppuVar5 + 1);
        if (cVar2 != '\0') {
          pppuVar5 = pppuVar1;
        }
      }
    }
    // Process the selected element
    FUN_0082abf0(pppuVar5);
    return param_2;
  }
  // Count is zero - initialize default data
  FUN_008334a0();
  local_34 = _DAT_00d5780c;
  local_30 = _DAT_00d5780c;
  local_2c = 0;
  local_80[0] = &PTR_LAB_00d736c0;
  local_20 = _DAT_00d735f0;
  uStack_1c = _UNK_00d735f4;
  uStack_18 = _UNK_00d735f8;
  uStack_14 = _UNK_00d735fc;
  FUN_0081f9f0(local_80);
  param_2[0x13] = local_34;
  param_2[0x14] = local_30;
  param_2[0x15] = local_2c;
  *param_2 = &PTR_LAB_00d736c0;
  param_2[0x18] = local_20;
  param_2[0x19] = uStack_1c;
  param_2[0x1a] = uStack_18;
  param_2[0x1b] = uStack_14;
  return param_2;
}