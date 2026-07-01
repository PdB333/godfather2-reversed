// FUNC_NAME: LinkedList::insertAfter
void __thiscall LinkedList::insertAfter(int this, int nodeToInsertAfter)
{
  int iVar1;
  int iVar2;
  
  if ((*(int *)(this + 4) != 0) && (*(int *)(*(int *)(this + 4) + 0x18) != 0)) {
    iVar1 = *(int *)(*(int *)(*(int *)(this + 0xc) + *(char *)(nodeToInsertAfter + 0x10) * 4) + 0x18);
    iVar2 = FUN_0081ca60(iVar1,*(undefined4 *)(iVar1 + 4),nodeToInsertAfter);
    FUN_0081d680(1);
    *(int *)(iVar1 + 4) = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
  }
  return;
}