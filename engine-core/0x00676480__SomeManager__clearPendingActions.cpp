// FUNC_NAME: SomeManager::clearPendingActions
void SomeManager::clearPendingActions(void)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int this; // unaff_ESI
  int iVar4;
  
  iVar4 = 1;
  if (0 < *(int *)(this + 0x21fc)) { // +0x21fc: count of pending actions
    do {
      iVar2 = *(int *)(*(int *)(this + 0x21f4) + iVar4 * 4); // +0x21f4: array of action pointers
      iVar3 = *(int *)(this + 0x222c); // +0x222c: some manager/allocator
      if (iVar2 != 0) {
        *(undefined4 *)(*(int *)(iVar3 + 0xc) + *(int *)(iVar2 + -8) * 4) = 0; // clear slot in allocator
        piVar1 = (int *)(iVar3 + 4);
        *piVar1 = *piVar1 + -1; // decrement allocator count
        (*DAT_01206694)(iVar2 + -0x10); // free memory (likely operator delete)
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 <= *(int *)(this + 0x21fc));
  }
  iVar4 = *(int *)(this + 0x21f4);
  if ((iVar4 != this + 0x2174) && (iVar2 = *(int *)(this + 0x222c), iVar4 != 0)) {
    *(undefined4 *)(*(int *)(iVar2 + 0xc) + *(int *)(iVar4 + -8) * 4) = 0;
    piVar1 = (int *)(iVar2 + 4);
    *piVar1 = *piVar1 + -1;
    (*DAT_01206694)(iVar4 + -0x10);
  }
  *(undefined4 *)(this + 0x21f8) = 0; // +0x21f8: clear pending flag or count
  return;
}