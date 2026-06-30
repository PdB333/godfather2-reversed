// FUNC_NAME: SIManager::releaseMembersAndDeallocate

void __fastcall SIManager::releaseMembersAndDeallocate(int this)
{
  int *basePtr;
  int **tablePtr;
  int tableBase;
  int freeCallback;
  
  // If non-null, maybe clear vtable or zero flag
  if (*(void ***)this != (void **)0x0) {
    *(undefined4 *)this = 0;
  }
  // Call internal cleanup subroutines (likely virtual or standalone)
  SIManager::cleanupFirstSubsystem();       // FUN_006754d0
  SIManager::cleanupSecondSubsystem();      // FUN_00675350
  
  // Release member at +0x28 (likely a reference-counted object)
  tablePtr = (int **)(this + 0x28);
  if (*tablePtr != (int *)0x0) {
    tableBase = **tablePtr;               // vtable / datablock
    // Null out entry in a slot table (memberRefSlots[slotIndex * 4] = 0)
    *(undefined4 *)(*(int *)(tableBase + 0xc) + tablePtr[-2] * 4) = 0;
    basePtr = (int *)(tableBase + 4);     // refcount field at +0x4
    *basePtr = *basePtr - 1;              // decrement
    // Free the object including its allocation header (pointer - 4)
    (*(void (*)(int *))DAT_01206694)(*tablePtr - 4);
  }
  
  // Release member at +0x38
  tablePtr = (int **)(this + 0x38);
  if (*tablePtr != (int *)0x0) {
    tableBase = **tablePtr;
    *(undefined4 *)(*(int *)(tableBase + 0xc) + tablePtr[-2] * 4) = 0;
    basePtr = (int *)(tableBase + 4);
    *basePtr = *basePtr - 1;
    (*(void (*)(int *))DAT_01206694)(*tablePtr - 4);
  }
  
  // Release member at +0x3c
  tablePtr = (int **)(this + 0x3c);
  if (*tablePtr != (int *)0x0) {
    tableBase = **tablePtr;
    *(undefined4 *)(*(int *)(tableBase + 0xc) + tablePtr[-2] * 4) = 0;
    basePtr = (int *)(tableBase + 4);
    *basePtr = *basePtr - 1;
    (*(void (*)(int *))DAT_01206694)(*tablePtr - 4);
  }
  
  // Call two more cleanup functions (maybe for arrays or streams)
  SIManager::cleanupThirdSubsystem();       // FUN_00675430 (called twice)
  SIManager::cleanupThirdSubsystem();
  
  // Release member at +0x2c
  tablePtr = (int **)(this + 0x2c);
  if (*tablePtr != (int *)0x0) {
    tableBase = **tablePtr;
    *(undefined4 *)(*(int *)(tableBase + 0xc) + tablePtr[-2] * 4) = 0;
    basePtr = (int *)(tableBase + 4);
    *basePtr = *basePtr - 1;
    (*(void (*)(int *))DAT_01206694)(*tablePtr - 4);
  }
  
  // Additional cleanup functions
  SIManager::cleanupFourthSubsystem();      // FUN_006755b0
  SIManager::cleanupFifthSubsystem();       // FUN_00675240
  SIManager::cleanupSixthSubsystem();       // FUN_0067a400
  
  // Release a raw pointer stored at +0x14 (might be a string or buffer)
  freeCallback = *(int *)(this + 0xb4);      // allocator / memory manager
  int headerSize = *(int *)(this + -0x8);    // slot index for this allocation
  if (*(int *)(this + 0x14) != 0) {
    // Null out entry in allocator's pointer table
    *(undefined4 *)(*(int *)(freeCallback + 0xc) + *(int *)(this + 0x14 - 8) * 4) = 0;
    basePtr = (int *)(freeCallback + 4);
    *basePtr = *basePtr - 1;                  // decrement total allocation count
    (*(void (*)(int *))DAT_01206694)(this + 0x14 - 0x10); // free the allocation (with 0x10 header)
  }
  
  // Release the main object itself (header at this - 0x10)
  *(undefined4 *)(*(int *)(freeCallback + 0xc) + *(int *)(this + -8) * 4) = 0;
  basePtr = (int *)(freeCallback + 4);
  *basePtr = *basePtr - 1;
  (*(void (*)(int *))DAT_01206694)(this - 0x10);
}