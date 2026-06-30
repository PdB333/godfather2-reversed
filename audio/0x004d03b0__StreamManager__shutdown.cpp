// FUNC_NAME: StreamManager::shutdown
void __thiscall StreamManager::shutdown(void)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  
  puVar5 = DAT_012234a8; // this pointer (StreamManager instance)
  // Free the active load requests list (field +0x10 first node)
  iVar1 = puVar5[4]; // +0x10: pActiveLoadRequests head
  while (iVar1 != 0) {
    puVar2 = (undefined4 *)puVar5[4]; // +0x10
    if (puVar2 != (undefined4 *)0x0) {
      if ((undefined4 *)puVar5[5] == puVar2) { // +0x14: pActiveLoadRequests tail matches
        puVar5[5] = 0; // clear tail
      }
      puVar5[4] = *puVar2; // move to next node
    }
    iVar1 = puVar5[4]; // +0x10
  }
  // Free the pending stream requests (field +0x5C linked list)
  iVar1 = puVar5[0x17]; // +0x5C: pPendingStreamRequests head
  while (iVar1 != 0) {
    piVar6 = (int *)puVar5[0x17]; // +0x5C
    piVar7 = (int *)0x0;
    if (piVar6 != (int *)0x0) {
      iVar1 = *piVar6; // next pointer
      puVar5[0x17] = iVar1; // update head
      piVar7 = piVar6;
      if (iVar1 == 0) {
        puVar5[0x18] = 0; // +0x60: clear tail
      }
      else {
        *(undefined4 *)(iVar1 + 4) = 0; // clear prev pointer of new head
        *piVar6 = 0; // clear next pointer of removed node
      }
    }
    FUN_00abd5c0(); // likely StreamRequest::release or destructor
    DeleteCriticalSection((LPCRITICAL_SECTION)(piVar7 + 0x3a)); // +0xE8: CriticalSection per request
    if (piVar7[0x36] != 0) { // +0xD8: some allocated buffer
      FUN_009c8f10(piVar7[0x36]); // free buffer
    }
    iVar1 = puVar5[0x17]; // +0x5C
  }
  // Drain the pending load semaphore (field +0x28, +0x24, +0x1C, +0x20)
  do {
    bVar4 = false;
    EnterCriticalSection((LPCRITICAL_SECTION)(puVar5 + 10)); // +0x28: csPendingLoad
    if (puVar5[9] != 0) { // +0x24: pendingLoadCount
      puVar5[8] = puVar5[8] + 1; // +0x20: pendingLoadHead
      if ((int)puVar5[7] <= (int)puVar5[8]) { // +0x1C: pendingLoadBufferSize
        puVar5[8] = 0; // wrap around
      }
      puVar5[9] = puVar5[9] + -1; // decrement pending count
      bVar4 = true;
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(puVar5 + 10)); // +0x28
  } while (bVar4);
  uVar3 = puVar5[2]; // +0x8: some callback or manager reference
  (**(code **)*puVar5)(0); // vtable[0]() - likely base class destructor
  piVar6 = (int *)FUN_009c8f80(); // memory manager allocation
  (**(code **)(*piVar6 + 4))(uVar3,0); // vtable[1]() - free operator delete
  return;
}