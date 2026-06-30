// FUNC_NAME: Sentient::validateInteractionTarget
void __thiscall Sentient::validateInteractionTarget(int thisPtr, int targetEntityId, int familyComponentPtr)
{
  char cVar1;
  int vtableResult;
  int *baseObject;
  
  // Get the base object pointer from this+8, offset subtracted by 0x48
  if (*(int *)(thisPtr + 8) == 0) {
    baseObject = (int *)0x0;
  }
  else {
    baseObject = (int *)(*(int *)(thisPtr + 8) + -0x48);
  }
  
  // Check bit 9 at flags offset 0x3c (interaction allowed?)
  if (((*(ushort *)(thisPtr + 0x3c) >> 9 & 1) != 0) && (baseObject != (int *)0x0)) {
    // If familyComponentPtr is not provided, attempt to retrieve it from the global manager
    if (familyComponentPtr == 0) {
      // DAT_01131040 is probably a static pointer to some manager singleton
      int managerResult = FUN_0043b870(DAT_01131040);
      if (((targetEntityId == 0) || (managerResult == 0)) ||
          (*(int *)(managerResult + 0x1c) == 0) || (*(int *)(managerResult + 0x1c) == 0x48)) {
        familyComponentPtr = 0;
      }
      else {
        familyComponentPtr = *(int *)(managerResult + 0x24);
      }
    }
    
    // Call virtual function at vtable offset 0x230 (likely getTargetId)
    vtableResult = (**(code **)(*baseObject + 0x230))();
    
    // If the result matches targetEntityId, or if family logic passes, set interaction flag
    if ((vtableResult != 0) &&
        ((vtableResult == targetEntityId ||
          ((familyComponentPtr != 0 &&
            ((*(int *)(familyComponentPtr + 0xc) == vtableResult ||
             (cVar1 = FUN_009a9b40(vtableResult), cVar1 != '\0')))))))) {
      // Set bit 0x400 at flags (interaction confirmed)
      *(ushort *)(thisPtr + 0x3c) = *(ushort *)(thisPtr + 0x3c) | 0x400;
    }
  }
  return;
}