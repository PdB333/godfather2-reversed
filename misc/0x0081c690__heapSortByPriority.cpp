// FUNC_NAME: heapSortByPriority
void heapSortByPriority(int base, int count, undefined4 param_3)

{
  undefined8 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = (count - base) / 0xc;
  iVar4 = iVar3 / 2;
  if (0 < iVar4) {
    iVar5 = base + iVar4 * 0xc;
    do {
      puVar1 = (undefined8 *)(iVar5 + -0xc);
      puVar2 = (undefined4 *)(iVar5 + -4);
      iVar4 = iVar4 + -1;
      iVar5 = iVar5 + -0xc;
      heapify(base, iVar4, iVar3, *puVar1, *puVar2, param_3);
    } while (0 < iVar4);
  }
  return;
}