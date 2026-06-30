// FUNC_NAME: StringTable::finalizeAndSort
undefined4 StringTable::finalizeAndSort(int param_1)

{
  int *piVar1;
  byte bVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  size_t _NumOfElements;
  int iVar7;
  bool bVar8;
  int local_14;
  byte *local_10;
  size_t local_c;
  
  if (DAT_0120589b != '\0') {
    return *(undefined4 *)(param_1 + 4);
  }
  _NumOfElements = 0;
  DAT_0120589b = 1;
  local_c = 0;
  iVar7 = DAT_01205a84;
  if (DAT_01205a84 != 0) {
    do {
      FUN_0065ffa0(local_c + 1);
      _NumOfElements = local_c + 1;
      piVar1 = (int *)(_NumOfElements * 4 + -4);
      if (piVar1 != (int *)0x0) {
        *piVar1 = iVar7;
      }
      iVar7 = *(int *)(iVar7 + 8);
      local_c = _NumOfElements;
    } while (iVar7 != 0);
  }
  _qsort((void *)0x0,_NumOfElements,4,(_PtFuncCompare *)&LAB_0065f670);
  iVar7 = 0;
  local_14 = 0;
  local_10 = &DAT_00e2f044;
  if (0 < (int)_NumOfElements) {
    do {
      puVar3 = *(undefined4 **)(iVar7 * 4);
      pbVar4 = (byte *)*puVar3;
      pbVar6 = local_10;
      do {
        bVar2 = *pbVar4;
        bVar8 = bVar2 < *pbVar6;
        if (bVar2 != *pbVar6) {
LAB_0065f770:
          iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_0065f775;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar4[1];
        bVar8 = bVar2 < pbVar6[1];
        if (bVar2 != pbVar6[1]) goto LAB_0065f770;
        pbVar4 = pbVar4 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar2 != 0);
      iVar5 = 0;
LAB_0065f775:
      if (iVar5 == 0) {
        puVar3[1] = local_14;
      }
      else {
        local_14 = local_14 + 1;
        puVar3[1] = local_14;
        local_10 = (byte *)**(undefined4 **)(iVar7 * 4);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < (int)_NumOfElements);
  }
  (*(code *)PTR__free_00f0cd8c)(0);
  return *(undefined4 *)(param_1 + 4);
}