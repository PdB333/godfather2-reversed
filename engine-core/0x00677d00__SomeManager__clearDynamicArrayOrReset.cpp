// FUNC_NAME: SomeManager::clearDynamicArrayOrReset
void FUN_00677d00(void)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int thisPtr; // in_EAX - implicit this pointer
  
  if (thisPtr != 0) {
    // Check if some pointer at +0x1c is non-null
    if (*(int *)(thisPtr + 0x1c) != 0) {
      // Compare with a value from the manager at +0x222c
      if (*(int *)(thisPtr + 0x1c) == *(int *)(*(int *)(thisPtr + 0x222c) + 0x48)) {
        // Set a flag at +0x80 to 1
        *(undefined4 *)(*(int *)(thisPtr + 0x222c) + 0x80) = 1;
      }
      else {
        // Call some other function (likely cleanup or error handling)
        FUN_00673160();
      }
    }
    // Call a function (likely to clear or reset something)
    FUN_00676480();
    
    // Process first dynamic array/list at +0x160
    iVar2 = *(int *)(thisPtr + 0x160);
    if ((iVar2 != thisPtr + 0xdc) && (iVar3 = *(int *)(thisPtr + 0x222c), iVar2 != 0)) {
      // Clear the slot in the manager's array at +0xc
      *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar2 + -8) * 4) = 0;
      // Decrement count at +0x4
      piVar1 = (int *)(iVar3 + 4);
      *piVar1 = *piVar1 + -1;
      // Free the memory (function pointer at 0x01206694)
      (*DAT_01206694)(iVar2 + -0x10);
    }
    
    // Process second dynamic array/list at +0xd0
    iVar2 = *(int *)(thisPtr + 0xd0);
    if ((iVar2 != thisPtr + 0x4c) && (iVar3 = *(int *)(thisPtr + 0x222c), iVar2 != 0)) {
      // Clear the slot in the manager's array at +0xc
      *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar2 + -8) * 4) = 0;
      // Decrement count at +0x4
      piVar1 = (int *)(iVar3 + 4);
      *piVar1 = *piVar1 + -1;
      // Free the memory (function pointer at 0x01206694)
      (*DAT_01206694)(iVar2 + -0x10);
    }
    
    // Reset a global flag
    DAT_012058ba = 0;
  }
  return;
}