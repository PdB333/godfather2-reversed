// FUNC_NAME: AnimationManager::releaseAnimationSlot
void AnimationManager::releaseAnimationSlot(int thisPtr, int *param_2)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  // Check if the animation slot is valid (not 0xFFFF)
  if (*(ushort *)(thisPtr + 0x1e1c) != 0xffff) {
    // Get the slot index (masked to 0x7F)
    uVar4 = *(ushort *)(thisPtr + 0x1e1c) & 0x7f;
    // Get the animation count from the slot data (offset +0x48, each slot is 0x3C bytes)
    iVar5 = (int)*(short *)(thisPtr + 0x48 + uVar4 * 0x3c);
    iVar2 = thisPtr + uVar4 * 0x3c;
    
    // Loop through all animations in this slot
    while (iVar5 = iVar5 + -1, -1 < iVar5) {
      // Call animation update function
      FUN_00674eb0();
      // Check if we should stop (param_2 indicates cancellation)
      if (*param_2 == 0) {
        // Call animation stop function
        FUN_00675d20();
      }
    }
    
    // Release the animation data pointers (offset +0x54, +0x4C, +0x50)
    iVar5 = *(int *)(iVar2 + 0x54);
    iVar3 = *(int *)(thisPtr + 0x1e38); // Animation data manager
    if (iVar5 != 0) {
      // Clear the reference in the animation data manager
      *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar5 + -8) * 4) = 0;
      piVar1 = (int *)(iVar3 + 4);
      *piVar1 = *piVar1 + -1;
      // Free the animation data
      (*DAT_01206694)(iVar5 + -0x10);
    }
    
    iVar5 = *(int *)(iVar2 + 0x4c);
    iVar3 = *(int *)(thisPtr + 0x1e38);
    if (iVar5 != 0) {
      *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar5 + -8) * 4) = 0;
      piVar1 = (int *)(iVar3 + 4);
      *piVar1 = *piVar1 + -1;
      (*DAT_01206694)(iVar5 + -0x10);
    }
    
    iVar2 = *(int *)(iVar2 + 0x50);
    iVar5 = *(int *)(thisPtr + 0x1e38);
    if (iVar2 != 0) {
      *(undefined4 *)(*(int *)(iVar5 + 0xc) + *(int *)(iVar2 + -8) * 4) = 0;
      piVar1 = (int *)(iVar5 + 4);
      *piVar1 = *piVar1 + -1;
      (*DAT_01206694)(iVar2 + -0x10);
    }
    
    // Mark the slot as invalid
    *(undefined2 *)(thisPtr + 0x1e1c) = 0xffff;
  }
  return;
}