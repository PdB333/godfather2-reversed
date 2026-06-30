// FUNC_NAME: PendingRequestProcessor::processRequest
undefined4 __thiscall PendingRequestProcessor::processRequest(int thisPtr, int requestObj, undefined4 param3, undefined4 param4, undefined4 param5)
{
  char cVar1;
  int iVar2;
  int *piVar3;
  int localListHead; // local_20
  int localListTail; // local_1c
  undefined4 localListData; // local_18
  int stackListHead; // iStack_14
  int stackListTail; // iStack_10
  undefined4 stackListData; // uStack_c

  // Check if requestObj is null or invalid, and also if internal pointers (+0x7c and +0x88) are null
  if (((requestObj == 0) || (iVar2 = isValidObject(requestObj), iVar2 == 0)) &&
      (iVar2 = *(int *)(thisPtr + 0x88), iVar2 == 0) &&
      (iVar2 = *(int *)(thisPtr + 0x7c), iVar2 == 0)) {
    // No pending work: clear status and set done flag
    *(undefined4 *)(thisPtr + 0xb0) = 0;
    *(uint *)(thisPtr + 0xb4) = *(uint *)(thisPtr + 0xb4) | 1;
    return 0;
  }

  // Initialize local list (empty)
  localListHead = 0;
  localListTail = 0;
  localListData = 0;

  // debug/profiling?
  FUN_005f5ce0();

  // Call the callback function pointer if set (+0xa4)
  if (*(code **)(thisPtr + 0xa4) != (code *)0x0) {
    (**(code **)(thisPtr + 0xa4))(thisPtr, thisPtr + 0x7c, thisPtr + 0x88, &localListHead, &localListHead);
  }

  FUN_005f5ce0();
  FUN_005f5ce0();

  // Initialize stack list
  stackListHead = 0;
  stackListTail = 0;
  stackListData = 0;

  // Parse param3 into a list starting at stackListHead
  cVar1 = FUN_00600720(param3, iVar2, &stackListHead, 0);
  if (cVar1 == '\0') {
    // Parsing failed: clear status, set done flag, and clean up lists
    *(undefined4 *)(thisPtr + 0xb0) = 0;
    *(uint *)(thisPtr + 0xb4) = *(uint *)(thisPtr + 0xb4) | 1;

    // Remove stackListHead from its list if non-empty (intrusive list removal)
    if (stackListHead != 0) {
      piVar3 = *(int **)(stackListHead + 4); // next pointer
      if (piVar3 == &stackListHead) {
        *(int *)(stackListHead + 4) = stackListTail;
      } else {
        // Find previous node (the one that points to stackListHead)
        while ((int *)piVar3[1] != &stackListHead) {
          piVar3 = (int *)piVar3[1];
        }
        piVar3[1] = stackListTail;
      }
    }

    // Remove localListHead from its list if non-empty
    if (localListHead != 0) {
      piVar3 = *(int **)(localListHead + 4);
      if (piVar3 == &localListHead) {
        *(int *)(localListHead + 4) = localListTail;
      } else {
        while ((int *)piVar3[1] != &localListHead) {
          piVar3 = (int *)piVar3[1];
        }
        piVar3[1] = localListTail;
      }
    }
    return 0;
  }

  // Parsing succeeded: process further using the parsed list
  FUN_00600a40(&stackListHead, param3, param4, param5, 0);

  // Clean up stackListHead list
  if (stackListHead != 0) {
    piVar3 = *(int **)(stackListHead + 4);
    if (piVar3 == &stackListHead) {
      *(int *)(stackListHead + 4) = stackListTail;
    } else {
      while ((int *)piVar3[1] != &stackListHead) {
        piVar3 = (int *)piVar3[1];
      }
      piVar3[1] = stackListTail;
    }
  }

  // Clean up localListHead list
  if (localListHead != 0) {
    piVar3 = *(int **)(localListHead + 4);
    if (piVar3 == &localListHead) {
      *(int *)(localListHead + 4) = localListTail;
    } else {
      while ((int *)piVar3[1] != &localListHead) {
        piVar3 = (int *)piVar3[1];
      }
      piVar3[1] = localListTail;
    }
  }

  return 1;
}