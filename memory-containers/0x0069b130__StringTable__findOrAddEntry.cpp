// FUNC_NAME: StringTable::findOrAddEntry
undefined4 __thiscall StringTable::findOrAddEntry(int this, undefined4 *key)
{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  iVar2 = *(int *)(this + 8);
  do {
    if (iVar2 == this + 4) {
      return 0;
    }
    if (key[1] == *(int *)(iVar2 + 0x24)) {
      if (key[1] == 0) {
LAB_0069b195:
        FUN_004d3e20(iVar2 + 0x10);
        return 1;
      }
      pbVar5 = *(byte **)(iVar2 + 0x20);
      pbVar3 = (byte *)*key;
      do {
        bVar1 = *pbVar3;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_0069b172:
          iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_0069b177;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_0069b172;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_0069b177:
      if (iVar4 == 0) goto LAB_0069b195;
    }
    iVar2 = FUN_00ab3c50(iVar2);
  } while( true );
}