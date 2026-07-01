// FUNC_NAME: heapSiftDown
void heapSiftDown(int heapBase, int heapEnd, undefined4 param_3)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = heapEnd - heapBase >> 3;
  iVar4 = iVar3 - (heapEnd - heapBase >> 0x1f) >> 1;
  if (0 < iVar4) {
    iVar5 = heapBase + iVar4 * 8;
    do {
      puVar1 = (undefined4 *)(iVar5 + -4);
      puVar2 = (undefined4 *)(iVar5 + -8);
      iVar5 = iVar5 + -8;
      iVar4 = iVar4 + -1;
      FUN_00878fb0(heapBase,iVar4,iVar3,*puVar2,*puVar1,param_3);
    } while (0 < iVar4);
  }
  return;
}