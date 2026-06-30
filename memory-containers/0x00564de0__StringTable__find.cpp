// FUNC_NAME: StringTable::find
undefined4 StringTable::find(int this, byte *key)
{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  uint uVar6;
  bool bVar7;
  
  uVar6 = 0;
  if (*(int *)(this + 0x1c) == 0) { // +0x1c: count of entries
    return 0;
  }
  puVar4 = (undefined4 *)(this + 8); // +0x08: array of string pointers
  do {
    pbVar2 = (byte *)(**(code **)(*(int *)*puVar4 + 0x14))(); // dereference string pointer, call virtual function at vtable+0x14 (likely getCString)
    pbVar5 = key;
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_00564e21:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_00564e26;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar7 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_00564e21;
      pbVar2 = pbVar2 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00564e26:
    if (iVar3 == 0) {
      return *(undefined4 *)(this + 8 + uVar6 * 4); // return the matching string pointer
    }
    uVar6 = uVar6 + 1;
    puVar4 = puVar4 + 1;
    if (*(uint *)(this + 0x1c) <= uVar6) { // +0x1c: count of entries
      return 0;
    }
  } while( true );
}