// FUNC_NAME: LinkedList::insertAfter
void LinkedList::insertAfter(int *param_1, int param_2, int param_3, int param_4, int param_5)
{
  int iVar1;
  int unaff_EDI;
  undefined1 local_8 [8];
  
  iVar1 = **(int **)(unaff_EDI + 0x1c); // +0x1c: pointer to list head node
  if ((param_2 == 0) || (param_2 != unaff_EDI)) {
    FUN_00b97aea(); // likely assertion failure
  }
  if (param_3 == iVar1) {
    iVar1 = *(int *)(unaff_EDI + 0x1c);
    if ((param_4 == 0) || (param_4 != unaff_EDI)) {
      FUN_00b97aea(); // assertion failure
    }
    if (param_5 == iVar1) {
      // Insert at head: update list head and fix up links
      FUN_006240a0(*(undefined4 *)(*(int *)(unaff_EDI + 0x1c) + 4)); // likely free node
      *(int *)(*(int *)(unaff_EDI + 0x1c) + 4) = *(int *)(unaff_EDI + 0x1c); // next = self
      *(undefined4 *)(unaff_EDI + 0x20) = 0; // +0x20: some count or flag
      *(undefined4 *)*(undefined4 *)(unaff_EDI + 0x1c) = *(undefined4 *)(unaff_EDI + 0x1c); // prev = self
      *(int *)(*(int *)(unaff_EDI + 0x1c) + 8) = *(int *)(unaff_EDI + 0x1c); // +0x08: some link
      param_1[1] = **(int **)(unaff_EDI + 0x1c);
      *param_1 = unaff_EDI;
      return;
    }
  }
  while( true ) {
    if ((param_2 == 0) || (param_2 != param_4)) {
      FUN_00b97aea(); // assertion failure
    }
    if (param_3 == param_5) break;
    FUN_00623fa0(); // likely advance iterator
    FUN_006217f0(unaff_EDI,local_8,param_2,param_3); // likely compare nodes
  }
  param_1[1] = param_3;
  *param_1 = param_2;
  return;
}