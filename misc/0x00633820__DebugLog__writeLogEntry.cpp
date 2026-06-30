// FUNC_NAME: DebugLog::writeLogEntry
void DebugLog::writeLogEntry(undefined4 param_1)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_EDI;
  undefined1 local_3c [60];
  
  // Get the associated singleton or manager object at +0x14
  piVar1 = *(int **)(unaff_EDI + 0x14);
  if ((piVar1[2] & 1U) == 0) { // Check if bit 0 of flags is not set
    if ((piVar1[2] & 2U) != 0) { // Check if bit 1 of flags is set (has string data)
      piVar1[3] = *(int *)piVar1[4]; // Copy pointer from +0x10 to +0x0C
    }
    // Get vtable pointer and offset +0x0C to get base class info
    iVar2 = *(int *)(*(int *)(*piVar1 + -4) + 0xc);
    // Calculate index: (current position - base offset >> 2) - 1
    iVar3 = (piVar1[3] - *(int *)(iVar2 + 0xc) >> 2) + -1;
    if (iVar3 < 0) {
      uVar4 = 0xffffffff; // Invalid index
    }
    else if (*(int *)(iVar2 + 0x14) == 0) {
      uVar4 = 0; // Null entry
    }
    else {
      uVar4 = *(undefined4 *)(*(int *)(iVar2 + 0x14) + iVar3 * 4); // Get the log entry value
    }
    // Format timestamp string into local buffer
    FUN_00636c20(local_3c,*(int *)(iVar2 + 0x20) + 0x10);
    // Print formatted log: timestamp:index:message
    FUN_00636c00("%s:%d: %s",local_3c,uVar4,param_1);
  }
  return;
}