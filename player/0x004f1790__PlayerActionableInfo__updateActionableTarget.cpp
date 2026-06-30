// FUNC_NAME: PlayerActionableInfo::updateActionableTarget
void __fastcall PlayerActionableInfo::updateActionableTarget(int this)
{
  uint *puVar1;
  int *piVar2;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  int unaff_FS_OFFSET;
  int iVar4;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Check if the action flag is already set (bit 0 of some flag)
  if ((*(byte *)(*(int *)(this + 0x10) + *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8)) & 1) == 0) {
    iVar4 = *(int *)(this + 4); // +0x04: pointer to some data structure
    uVar3 = *(undefined4 *)(iVar4 + 0xb4); // +0xB4: some value
    if (*(int *)(iVar4 + 0xbc) == 0) { // +0xBC: check if some pointer is null
      // Direct copy of position/rotation data
      local_20 = *(undefined4 *)(iVar4 + 0x60); // +0x60: x position
      uStack_1c = *(undefined4 *)(iVar4 + 100); // +0x64: y position
      uStack_18 = *(undefined4 *)(iVar4 + 0x68); // +0x68: z position
      uStack_14 = *(undefined4 *)(iVar4 + 0x6c); // +0x6C: some rotation/quaternion
    }
    else {
      // Transform data using some function (likely matrix/transform)
      FUN_0056b420(iVar4 + 0x30, *(int *)(iVar4 + 0xbc), &local_20);
      uVar3 = extraout_EDX;
    }
    piVar2 = *(int **)(this + 0x24); // +0x24: pointer to some data
    iVar4 = *piVar2;
    // Call a function to set the actionable target with position/rotation
    (**(code **)(**(int **)(DAT_012234c4 + 0x1c) + 4))
              (uVar3, CONCAT44(uStack_1c, local_20), uStack_18, iVar4, piVar2[1], piVar2[2], DAT_00e2eff4);
    puVar1 = (uint *)(*(int *)(this + 0x10) + *(int *)(iVar4 + 8));
    *puVar1 = *puVar1 | 1; // Set the action flag (bit 0)
    iVar4 = *(int *)(this + 0x24);
    // Check if the target has valid dimensions (width and height > 0) and some global flag is set
    if (((0.0 < *(float *)(iVar4 + 0xc)) && (0.0 < *(float *)(iVar4 + 0x10))) && (DAT_012233c4 != 0)) {
      FUN_00416340(&stack0xffffffc0, *(undefined4 *)(iVar4 + 0x10), 4); // Some debug/visualization call
    }
  }
  return;
}