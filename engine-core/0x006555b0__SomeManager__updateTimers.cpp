// FUNC_NAME: SomeManager::updateTimers
void SomeManager::updateTimers(void)
{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int this; // unaff_EDI - this pointer
  
  uVar2 = FUN_0065c190(); // getCurrentTime() or similar
  *(uint *)(this + 100) = uVar2; // +0x64: currentTime
  FUN_0065ca60(); // processExpiredTimers() or similar
  iVar3 = *(int *)(this + 0x80); // +0x80: pendingActionList head
  while ((iVar3 != 0 &&
         (piVar1 = *(int **)(this + 0x80), (uint)piVar1[6] < *(uint *)(this + 100)))) {
    iVar3 = *piVar1; // next node
    FUN_00658230(this + 0x5c, piVar1 + 8, piVar1[7], 0); // executeAction(this->actionQueue, actionData, actionType, 0)
    (*(code *)PTR__free_00f0cd8c)(*(undefined4 *)(this + 0x80)); // free pending node
    *(int *)(this + 0x80) = iVar3;
  }
  FUN_0064d6e0(); // updateTimers() or processFrameTimers()
  iVar3 = 0;
  if (0 < *(int *)(this + 0xc)) { // +0x0C: numSubManagers
    do {
      FUN_00653c20(); // subManager->update()
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(this + 0xc));
  }
  if (*(int *)(this + 0x6c) + 0x5dcU < *(uint *)(this + 100)) { // +0x6C: lastCleanupTime, 0x5dc = 1500ms
    iVar3 = 0;
    *(uint *)(this + 0x6c) = *(uint *)(this + 100);
    if (0 < *(int *)(this + 0xc)) {
      do {
        FUN_00652fe0(); // subManager->cleanup()
        iVar3 = iVar3 + 1;
      } while (iVar3 < *(int *)(this + 0xc));
    }
  }
  return;
}