// FUNC_NAME: SomeList::removeNodeFromList
void __fastcall SomeList::removeNodeFromList(int param_1)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int local_4;
  
  piVar1 = (int *)(param_1 + 0x1f0); // +0x1F0: pointer to node in list
  if (*(int *)(param_1 + 0x1f0) == 0) {
    local_4 = param_1;
    piVar3 = (int *)FUN_008dc310(&local_4,param_1 + 0x1e0); // +0x1E0: some list head or iterator
    if (*piVar1 != 0) {
      *(undefined4 *)(*piVar1 + 8) = 0; // clear next pointer of node
      *piVar1 = 0;
    }
    iVar2 = *piVar3;
    *piVar1 = iVar2;
    if (iVar2 != 0) {
      *(int **)(iVar2 + 8) = piVar1; // set previous pointer of next node
      *piVar3 = 0;
    }
    if (local_4 != 0) {
      *(undefined4 *)(local_4 + 8) = 0; // clear next pointer of previous node
    }
  }
  return;
}