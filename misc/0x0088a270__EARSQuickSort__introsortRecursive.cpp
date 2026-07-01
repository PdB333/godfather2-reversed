// FUNC_NAME: EARSQuickSort::introsortRecursive
void introsortRecursive(int *arrBegin, int *arrEnd, int maxDepth, undefined4 param_4)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  
  uVar5 = arrEnd - (int)arrBegin;
  while ((0x70 < (int)(uVar5 & 0xfffffffc) && (0 < maxDepth))) {
    uVar5 = *(uint *)(*(int *)(*(int *)(arrEnd[-1] + 0x14) + 0x60);
    uVar1 = *(uint *)(*(int *)(*arrBegin + 0x14) + 0x60);
    iVar6 = (arrEnd - (int)arrBegin >> 2) - (arrEnd - (int)arrBegin >> 0x1f) >> 1;
    uVar2 = *(uint *)(*(int *)(arrBegin[iVar6] + 0x14) + 0x60);
    uVar3 = uVar2;
    piVar4 = arrBegin + iVar6;
    piVar7 = arrBegin;
    if (uVar1 < uVar2) {
      uVar3 = uVar1;
      piVar4 = arrBegin;
      piVar7 = arrBegin + iVar6;
      uVar1 = uVar2;
    }
    if ((uVar5 <= uVar1) && (piVar7 = piVar4, uVar3 < uVar5)) {
      piVar7 = (int *)(arrEnd + -1);
    }
    iVar6 = partitionSelectPivot(arrBegin, arrEnd, piVar7, param_4);
    maxDepth = maxDepth + -1;
    introsortRecursive(iVar6, arrEnd, maxDepth, param_4);
    uVar5 = iVar6 - (int)arrBegin;
    arrEnd = iVar6;
  }
  if (maxDepth == 0) {
    heapsortRange(arrBegin, arrEnd, arrEnd, param_4);
  }
  return;
}