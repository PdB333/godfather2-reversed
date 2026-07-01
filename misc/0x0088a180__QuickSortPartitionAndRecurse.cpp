// FUNC_NAME: QuickSortPartitionAndRecurse
void QuickSortPartitionAndRecurse(int base, int end, int depth, undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = end - base;
  while ((0x1c < iVar6 / 0x50 && (0 < depth))) {
    uVar1 = *(uint *)(base + 8);
    iVar4 = ((end - base) / 0xa0) * 0x50;
    uVar2 = *(uint *)(iVar4 + 8 + base);
    iVar4 = iVar4 + base;
    uVar3 = uVar2;
    iVar6 = iVar4;
    iVar5 = base;
    if (uVar1 < uVar2) {
      uVar3 = uVar1;
      iVar6 = base;
      iVar5 = iVar4;
      uVar1 = uVar2;
    }
    if ((*(uint *)(end + -0x48) <= uVar1) && (iVar5 = iVar6, uVar3 < *(uint *)(end + -0x48))
       ) {
      iVar5 = end + -0x50;
    }
    iVar5 = FUN_008899c0(base,end,iVar5,param_4);
    depth = depth + -1;
    QuickSortPartitionAndRecurse(iVar5,end,depth,param_4);
    iVar6 = iVar5 - base;
    end = iVar5;
  }
  if (depth == 0) {
    FUN_00889a40(base,end,end,param_4);
  }
  return;
}