// FUNC_NAME: StringTable::findOrAddString
uint StringTable::findOrAddString(byte *key, int param_2)
{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  int unaff_EDI;
  bool bVar8;
  int local_4;
  
  uVar5 = 0;
  if (*(int *)(unaff_EDI + 0xc) == 0) {
    iVar6 = 0;
  }
  else {
    iVar6 = (*(int *)(unaff_EDI + 0x10) - *(int *)(unaff_EDI + 0xc)) / 0x28; // 0x28 = 40 bytes per entry
  }
  if (0 < iVar6) {
    local_4 = 0;
    do {
      if ((*(int *)(unaff_EDI + 0xc) == 0) ||
         ((uint)((*(int *)(unaff_EDI + 0x10) - *(int *)(unaff_EDI + 0xc)) / 0x28) <= uVar5)) {
        FUN_00b97aea(); // likely assertion/error handler
      }
      pbVar7 = (byte *)(*(int *)(unaff_EDI + 0xc) + local_4);
      pbVar2 = pbVar7;
      pbVar4 = param_1;
      do {
        bVar1 = *pbVar2;
        bVar8 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_005d9713:
          iVar3 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_005d9718;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar8 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_005d9713;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_005d9718:
      if ((iVar3 == 0) && ((iVar3 = *(int *)(pbVar7 + 0x20), iVar3 == param_2 || (iVar3 < 0)))) {
        return uVar5;
      }
      local_4 = local_4 + 0x28;
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < iVar6);
  }
  return 0xffffffff;
}