// FUNC_NAME: some_iterator_or_tree_advance
void FUN_006243f0(void)
{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *unaff_ESI; // this pointer / iterator state
  
  if (*unaff_ESI == 0) {
    FUN_00b97aea(); // likely error/assert
  }
  iVar2 = unaff_ESI[1]; // current node
  if (*(char *)(iVar2 + 0x15) == '\0') { // node is not marked (e.g., "not visited" or "not a leaf"?)
    piVar3 = *(int **)(iVar2 + 8); // left child pointer (or parent?)
    if (*(char *)((int)piVar3 + 0x15) != '\0') {
      iVar2 = *(int *)(iVar2 + 4); // right child pointer
      cVar1 = *(char *)(iVar2 + 0x15);
      while ((cVar1 == '\0' && (unaff_ESI[1] == *(int *)(iVar2 + 8)))) {
        unaff_ESI[1] = iVar2;
        iVar2 = *(int *)(iVar2 + 4);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
      unaff_ESI[1] = iVar2;
      return;
    }
    cVar1 = *(char *)(*piVar3 + 0x15);
    piVar4 = (int *)*piVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*piVar4 + 0x15);
      piVar3 = piVar4;
      piVar4 = (int *)*piVar4;
    }
    unaff_ESI[1] = (int)piVar3;
    return;
  }
  FUN_00b97aea(); // error/assert
  return;
}