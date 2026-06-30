// FUNC_NAME: MemoryAllocator::allocateAligned
int MemoryAllocator::allocateAligned(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *unaff_ESI;
  
  if ((*unaff_ESI == 0) || (unaff_ESI[1] < *(int *)(*unaff_ESI + 8) + param_1)) {
    piVar2 = (int *)FUN_009c8e50(0xc);
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      iVar3 = FUN_009c8e80(unaff_ESI[1]);
      piVar2[1] = iVar3;
    }
    *piVar2 = *unaff_ESI;
    piVar2[2] = 0;
    *unaff_ESI = (int)piVar2;
  }
  iVar3 = *unaff_ESI;
  iVar1 = *(int *)(iVar3 + 8);
  *(uint *)(iVar3 + 8) = (param_1 + 3U & 0xfffffffc) + iVar1;
  return *(int *)(iVar3 + 4) + iVar1;
}