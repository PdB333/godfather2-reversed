// FUNC_NAME: MissionManager::completeMission
void __fastcall MissionManager::completeMission(int this)
{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int local_1c;
  undefined **ppuStack_18;
  int iStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined ***pppuStack_8;
  undefined1 uStack_4;
  
  // Check if mission is already completed (bit 4 of flags at +0x84)
  if ((*(uint *)(this + 0x84) >> 4 & 1) == 0) {
    // Clear objective timers at +0x108 and +0x114
    FUN_008c1ee0(this + 0x108);
    FUN_008c1ee0(this + 0x114);
    
    uVar3 = 0;
    // Get global game manager instance (DAT_012233a0 + 4)
    if (**(int **)(DAT_012233a0 + 4) == 0) {
      local_1c = 0;
    }
    else {
      local_1c = **(int **)(DAT_012233a0 + 4) + -0x1f30;
    }
    
    // Iterate through mission objectives (array at +0x1a4, count at +0x1a8)
    if (*(int *)(this + 0x1a8) != 0) {
      do {
        iVar2 = *(int *)(*(int *)(this + 0x1a4) + uVar3 * 4);
        // Check if objective type is not 7 (completed/disabled)
        if (*(int *)(iVar2 + 4) != 7) {
          // If objective has a target entity (+0x8) and can get its manager
          if ((*(int *)(iVar2 + 8) != 0) && (piVar1 = (int *)FUN_00791300(), piVar1 != (int *)0x0))
          {
            // Notify manager of objective completion (0xb = complete, local_1c = player index)
            (**(code **)(*piVar1 + 0x288))(0xb, local_1c, 0);
          }
          // Get objective's target entity data
          iVar2 = FUN_008c12a0(*(undefined4 *)(iVar2 + 8));
          // If entity exists, is not completed, and passes validation
          if (((iVar2 != 0) && (*(int *)(iVar2 + 4) != 7)) &&
             (FUN_008c8a80(1), *(int *)(iVar2 + 4) != 7)) {
            // Clear objective and set to completed state
            FUN_008c80d0(0);
            FUN_008c8a20(7, 0);
          }
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(this + 0x1a8));
    }
    
    // Set mission completed flag (bit 4)
    *(uint *)(this + 0x84) = *(uint *)(this + 0x84) | 0x10;
    
    // Play mission complete sound (6 = mission complete, +0x54 = sound context)
    FUN_0093f6c0(6, *(undefined4 *)(this + 0x54), 0);
    
    // Send network event (0x6a194e56 = mission complete hash)
    FUN_007e8d90(this, 0x6a194e56);
    
    // Trigger mission complete UI event (0x602533fd = mission complete hash)
    FUN_00894c90(0x602533fd);
    
    // Setup stack frame for cleanup
    iStack_14 = this + 0x48;
    ppuStack_18 = &PTR_FUN_00e31e2c;
    uStack_10 = 0;
    if (iStack_14 != 0) {
      uStack_10 = *(undefined4 *)(this + 0x4c);
      *(int **)(this + 0x4c) = &iStack_14;
    }
    pppuStack_8 = &ppuStack_18;
    uStack_c = DAT_0112f940;
    uStack_4 = 0;
    FUN_00408a00(&uStack_c, 0);
    if (iStack_14 != 0) {
      FUN_004daf90(&iStack_14);
    }
  }
  return;
}