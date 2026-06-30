// FUNC_NAME: PlayerF2FSM::updateState
undefined4 * PlayerF2FSM::updateState(undefined4 *this, int param_2, int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  char cVar5;
  undefined1 uVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  int *piVar11;
  int unaff_FS_OFFSET;
  int *local_64;
  undefined4 *local_60;
  undefined4 local_5c;
  uint uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  FUN_00533cc0(); // likely some engine init or frame start
  *this = &PTR_FUN_00e378b0; // vtable setup
  if (*(char *)(param_2 + 0xd) != '\0') { // check if state is already done
    return this;
  }
  iVar2 = *(int *)(this[1] + 0xc4); // +0xC4: some pointer offset
  if (iVar2 == 0) {
    local_64 = (int *)0x0;
  }
  else {
    local_64 = (int *)(iVar2 + -0x48); // adjust pointer
  }
  iVar2 = *(int *)(this[1] + 0x20); // +0x20: another pointer
  local_5c = 0xffffffff;
  uVar6 = 1;
  bVar4 = false;
  if (iVar2 != 0) {
    *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1; // ref count increment
  }
  piVar7 = (int *)FUN_004f76d0(iVar2); // get some object from pool
  local_60 = (undefined4 *)0x0;
  if (piVar7 == (int *)0x0) {
    uVar10 = *(uint *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + this[4]); // +0x10: some index
    if ((uVar10 & 0x40) == 0) {
      if ((uVar10 & 4) == 0) {
        local_64 = (int *)0x0;
      }
      else {
        local_5c = *(undefined4 *)(this[1] + 0xb8); // +0xB8: some value
      }
    }
    else {
      FUN_00533fb0(); // likely error handling
      local_64 = (int *)0x0;
    }
  }
  else {
    cVar5 = (**(code **)(*piVar7 + 0x14))(); // virtual call: isActive?
    if (cVar5 == '\0') {
      *(undefined1 *)(param_2 + 0xc) = 1; // mark state as done
      return this;
    }
    if (piVar7[5] == 0) {
      local_64 = (int *)0x0;
    }
    else {
      local_64 = (int *)(piVar7[5] + -0x48); // adjust pointer
    }
    local_5c = (**(code **)(*piVar7 + 0x34))(); // virtual call: getSomeValue
    uVar6 = (**(code **)(*piVar7 + 0x1c))(); // virtual call: getSomeFlag
    puVar8 = (undefined4 *)(**(code **)(*piVar7 + 0x28))(); // virtual call: getTarget1
    puVar9 = (undefined4 *)(**(code **)(*piVar7 + 0x2c))(); // virtual call: getTarget2
    if ((((float)piVar7[0x28] < *(float *)(param_3 + 0xac)) && (puVar9 != (undefined4 *)0x0)) ||
       (puVar9 = puVar8, puVar8 != (undefined4 *)0x0)) {
      local_60 = puVar9;
      if (local_60 != (undefined4 *)0x0) goto LAB_004f7394;
    }
    else {
      bVar4 = true;
    }
  }
  uVar10 = (uint)*(char *)(param_3 + 0x47); // +0x47: some state index
  if (uVar10 == 3) {
    uVar10 = FUN_004e9200(); // random number
    uVar10 = uVar10 % 3;
  }
  iVar2 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);
  iVar3 = this[4]; // +0x10: some index
  puVar9 = (undefined4 *)((uVar10 + 5) * 0x10 + iVar3 + iVar2);
  uStack_50 = *puVar9;
  uStack_4c = puVar9[1];
  uStack_48 = puVar9[2];
  uStack_44 = puVar9[3];
  uVar10 = 0x21 >> ((char)uVar10 * '\x04' & 0x1fU) & 0xf;
  puVar9 = (undefined4 *)((uVar10 + 5) * 0x10 + iVar3 + iVar2);
  uStack_40 = *puVar9;
  uStack_3c = puVar9[1];
  uStack_38 = puVar9[2];
  uStack_34 = puVar9[3];
  puVar9 = (undefined4 *)
           (((0x21 >> ((char)uVar10 * '\x04' & 0x1fU) & 0xfU) + 5) * 0x10 + iVar3 + iVar2);
  uStack_30 = *puVar9;
  uStack_2c = puVar9[1];
  uStack_28 = puVar9[2];
  uStack_24 = puVar9[3];
  puVar9 = (undefined4 *)(iVar3 + 0x80 + iVar2);
  uStack_20 = *puVar9;
  uStack_1c = puVar9[1];
  uStack_18 = puVar9[2];
  uStack_14 = puVar9[3];
LAB_004f7394:
  bVar1 = *(byte *)(param_3 + 0x44); // +0x44: flags
  if (local_64 == (int *)0x0) {
    piVar7 = (int *)0x0;
  }
  else {
    uStack_54 = 0;
    cVar5 = (**(code **)(*local_64 + 0x10))(0x77a210a2,&uStack_54); // virtual call: find by ID
    piVar7 = (int *)(-(uint)(cVar5 != '\0') & uStack_54);
  }
  if (local_60 == (undefined4 *)0x0) {
    if (bVar4) {
      local_60 = (undefined4 *)(this[1] + 0x30); // +0x30: default target
    }
    else {
      local_60 = &uStack_50; // use computed target
    }
  }
  if ((piVar7 == (int *)0x0) || ((bVar1 >> 6 & 1) != 0)) {
    FUN_00525b90(*(undefined4 *)(this[1] + 0x10),param_3,local_5c,uVar6); // single target action
  }
  else {
    piVar7 = (int *)(**(code **)(*piVar7 + 0x14c))(); // virtual call: getFirstChild
    if (piVar7 != (int *)0x0) {
      do {
        if (piVar7 == (int *)0x0) {
          piVar11 = (int *)0x0;
        }
        else {
          piVar11 = piVar7 + 0x15; // +0x54: offset to some data
        }
        uStack_54 = DAT_01206880; // some global constant
        FUN_00525970(*(undefined4 *)(this[1] + 0x10),param_3,piVar11,local_5c,uVar6,local_60); // multi-target action
        piVar7 = (int *)(**(code **)(*piVar7 + 0x150))(); // virtual call: getNextSibling
      } while (piVar7 != (int *)0x0);
      *(undefined1 *)(param_2 + 0xc) = 1; // mark state as done
      return this;
    }
  }
  *(undefined1 *)(param_2 + 0xc) = 1; // mark state as done
  return this;
}