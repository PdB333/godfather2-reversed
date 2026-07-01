// FUNC_NAME: HUDTargetingSystem::initializeTargetingElements
void __thiscall HUDTargetingSystem::initializeTargetingElements(int thisPtr, int param_2)
{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  int local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined1 local_20 [28];
  
  if ((*(byte *)(thisPtr + 0x10) & 1) == 0) {
    FUN_0081dce0(); // some initialization function
    iVar5 = FUN_004262f0(0); // get screen dimensions or something
    local_40 = *(undefined4 *)(thisPtr + 0x108);
    local_3c = *(undefined4 *)(thisPtr + 0x10c);
    local_38 = *(undefined4 *)(thisPtr + 0x110);
    iVar1 = iVar5 + 0x40;
    local_34 = _DAT_00d5780c; // global constant
    local_48 = iVar1;
    local_2c = iVar5;
    if ((param_2 == 0) ||
       ((((*(int *)(param_2 + 0x4d0) == 0 && (*(int *)(param_2 + 0x4d4) == 0)) &&
         (*(int *)(param_2 + 0x4d8) == 0)) && (*(int *)(param_2 + 0x4dc) == 0)))) {
      // No valid targeting data from param_2, create default free-aim targeting element
      local_24 = &local_40;
      local_28 = 0xffffffff;
      local_30 = 5;
      FUN_004eacb0("hud_targeting_freeaim"); // get resource by name
      piVar7 = (int *)FUN_004df3c0(&local_44,local_20,iVar1,0x1ff,0,&local_30); // create UI element
      piVar2 = (int *)(thisPtr + 0xe0); // pointer to free-aim element slot
      if (*(int *)(thisPtr + 0xe0) != 0) {
        *(undefined4 *)(*(int *)(thisPtr + 0xe0) + 8) = 0;
        *piVar2 = 0;
      }
      iVar1 = *piVar7;
      *piVar2 = iVar1;
      if (iVar1 != 0) {
        *(int **)(iVar1 + 8) = piVar2;
        *piVar7 = 0;
      }
      if (local_44 != 0) {
        *(undefined4 *)(local_44 + 8) = 0;
      }
      // Create center targeting element
      local_24 = &local_40;
      local_28 = 0xffffffff;
      local_30 = 5;
      local_2c = iVar5;
      FUN_004eacb0("hud_targeting_center");
      piVar7 = (int *)FUN_004df3c0(&local_44,local_20,local_48,0x1ff,0,&local_30);
      piVar2 = (int *)(thisPtr + 0xe4); // pointer to center element slot
      if (*(int *)(thisPtr + 0xe4) != 0) {
        *(undefined4 *)(*(int *)(thisPtr + 0xe4) + 8) = 0;
        *piVar2 = 0;
      }
      iVar1 = *piVar7;
      *piVar2 = iVar1;
      if (iVar1 != 0) {
        *(int **)(iVar1 + 8) = piVar2;
        *piVar7 = 0;
      }
      if (local_44 != 0) {
        *(undefined4 *)(local_44 + 8) = 0;
      }
      // Update free-aim element position
      FUN_004df830(*(undefined4 *)(thisPtr + 0xf8));
      iVar1 = *(int *)(thisPtr + 0xf8);
      uVar6 = *(undefined4 *)(thisPtr + 0x24);
      uVar3 = *(undefined4 *)(thisPtr + 0x28);
      uVar4 = *(undefined4 *)(thisPtr + 0x2c);
      *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(thisPtr + 0x20);
      *(undefined4 *)(iVar1 + 0x14) = uVar6;
      *(undefined4 *)(iVar1 + 0x18) = uVar3;
      *(undefined4 *)(iVar1 + 0x1c) = uVar4;
    }
    else {
      // Use targeting data from param_2 (e.g., from a weapon or character)
      local_24 = &local_40;
      local_28 = 0xffffffff;
      local_30 = 5;
      uVar6 = FUN_004df270(&local_48,(int *)(param_2 + 0x4d0),iVar1,0x1ff,0,&local_30);
      FUN_00414db0(uVar6); // set texture or something
      if (local_48 != 0) {
        *(undefined4 *)(local_48 + 8) = 0;
      }
    }
    // Update center element position
    FUN_004df830(*(undefined4 *)(thisPtr + 0xf4));
    iVar1 = *(int *)(thisPtr + 0xf4);
    uVar6 = *(undefined4 *)(thisPtr + 0x24);
    uVar3 = *(undefined4 *)(thisPtr + 0x28);
    uVar4 = *(undefined4 *)(thisPtr + 0x2c);
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(thisPtr + 0x20);
    *(undefined4 *)(iVar1 + 0x14) = uVar6;
    *(undefined4 *)(iVar1 + 0x18) = uVar3;
    *(undefined4 *)(iVar1 + 0x1c) = uVar4;
    *(uint *)(thisPtr + 0x10) = *(uint *)(thisPtr + 0x10) | 1; // mark as initialized
    if (*(int *)(thisPtr + 0x14) != 0) {
      FUN_0081dd40(*(int *)(thisPtr + 0x14)); // cleanup old data
    }
  }
  return;
}