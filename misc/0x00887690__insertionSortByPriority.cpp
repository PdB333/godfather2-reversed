// FUNC_NAME: insertionSortByPriority
void insertionSortByPriority(int *begin, int *end)
{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  if (begin != end) {
    for (piVar3 = begin + 1; piVar3 != end; piVar3 = piVar3 + 1) {
      iVar1 = *piVar3;
      piVar2 = piVar3;
      while ((piVar2 != begin &&
             (*(uint *)(*(int *)(iVar1 + 0x14) + 0x60) <
              *(uint *)(*(int *)(piVar2[-1] + 0x14) + 0x60)))) {
        *piVar2 = piVar2[-1];
        piVar2 = piVar2 + -1;
      }
      *piVar2 = iVar1;
    }
  }
  return;
}