// FUNC_NAME: SomeManager::processPendingItems
undefined4 FUN_00699f30(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  undefined1 local_24 [4];
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14;
  uint local_10 [3];
  code *local_4;
  
  piVar4 = DAT_01129f8c;
  if (DAT_01129f8c != DAT_01129f90) {
    do {
      iVar1 = *piVar4;
      FUN_004d3bc0(param_1);  // likely some per-item setup or lock
      local_20 = 0;
      local_1c = 0;
      local_18 = 0;
      local_14 = (code *)0x0;
      piVar3 = (int *)FUN_00698c00(local_24,local_10);  // get item data
      iVar2 = *piVar3;
      bVar5 = iVar2 != iVar1 + 0xc;  // check if item type matches expected
      if (bVar5) {
        FUN_004d3e20(iVar2 + 0x20);  // process item with offset
      }
      if (local_20 != 0) {
        (*local_14)(local_20);  // call cleanup callback
      }
      if (local_10[0] != 0) {
        (*local_4)(local_10[0]);  // call another cleanup callback
      }
      if (bVar5) {
        return 1;  // item processed
      }
      piVar4 = piVar4 + 1;
    } while (piVar4 != DAT_01129f90);
  }
  return 0;  // no items processed
}