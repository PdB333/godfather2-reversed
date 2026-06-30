// FUNC_NAME: StringTable::findOrInsertString
undefined4 StringTable::findOrInsertString(undefined4 param_1, byte *param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 uVar5;
  int unaff_EDI;
  bool bVar6;
  
  iVar2 = FUN_00625f80(); // likely lockMutex or beginRead
  if (iVar2 != 0) {
    FUN_00625e70(); // likely some init or check
    iVar2 = *(int *)(unaff_EDI + 8); // this+0x08: current bucket index or pointer
    if ((int *)(iVar2 + -8) != (int *)0x0) {
      if (*(int *)(iVar2 + -8) == 4) { // check type tag? 4 = string type?
        pbVar3 = (byte *)(*(int *)(iVar2 + -4) + 0x10); // +0x10: string data offset
      }
      else {
        iVar4 = FUN_00633990(); // likely resolveIndirection or getStringData
        if (iVar4 == 0) {
          pbVar3 = (byte *)0x0;
        }
        else {
          pbVar3 = (byte *)(*(int *)(iVar2 + -4) + 0x10);
        }
        if (*(uint *)(*(int *)(unaff_EDI + 0x10) + 0x20) <= // this+0x10->+0x20: some count
            *(uint *)(*(int *)(unaff_EDI + 0x10) + 0x24)) { // this+0x10->+0x24: threshold
          FUN_00627360(); // likely growTable or rehash
        }
      }
      if (pbVar3 != (byte *)0x0) {
        do {
          bVar1 = *pbVar3;
          bVar6 = bVar1 < *param_2;
          if (bVar1 != *param_2) {
LAB_00627ee0:
            iVar2 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_00627ee5;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar6 = bVar1 < param_2[1];
          if (bVar1 != param_2[1]) goto LAB_00627ee0;
          pbVar3 = pbVar3 + 2;
          param_2 = param_2 + 2;
        } while (bVar1 != 0);
        iVar2 = 0;
LAB_00627ee5:
        if (iVar2 == 0) { // strings match
          *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + -8; // adjust bucket pointer
          uVar5 = FUN_00625b60(); // likely returnStringHandle or getStringId
          return uVar5;
        }
      }
    }
    *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + -8; // cleanup bucket pointer
  }
  return 0;
}