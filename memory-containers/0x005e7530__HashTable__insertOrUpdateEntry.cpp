// FUNC_NAME: HashTable::insertOrUpdateEntry
uint __thiscall HashTable::insertOrUpdateEntry(undefined4 *param_1, undefined4 *param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  byte bVar4;
  undefined4 uVar5;
  uint in_EAX;
  uint uVar6;
  undefined4 *puVar7;
  int unaff_ESI;
  byte local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  bVar4 = *(byte *)(unaff_ESI + 0x1c); // +0x1c: table size (number of buckets)
  uVar6 = in_EAX ^ 0xad103100; // hash computation with seed
  if (bVar4 <= uVar6) {
    return uVar6 & 0xffffff00; // hash out of range, return error
  }
  puVar7 = (undefined4 *)FUN_0056b8a0(param_1[1],*param_1,param_1[2],&local_50); // allocate or find bucket
  if (bVar4 != 0) {
    local_54 = (byte)in_EAX;
    puVar7 = (undefined4 *)CONCAT31((int3)((uint)puVar7 >> 8),local_54);
    if ((local_54 < bVar4) &&
       (puVar7 = *(undefined4 **)(unaff_ESI + 4 + (uVar6 & 0xff) * 4), puVar7 != (undefined4 *)0x0))
    {
      uVar1 = param_2[1];
      uVar2 = param_2[2];
      puVar7[4] = local_4c;
      puVar7[5] = local_3c;
      *puVar7 = local_50;
      puVar7[6] = local_2c;
      puVar7[1] = local_40;
      puVar7[8] = local_48;
      puVar7[2] = local_30;
      puVar7[9] = local_38;
      puVar7[3] = 0;
      puVar7[7] = 0;
      puVar7[0xb] = 0;
      puVar7[0xc] = 0;
      puVar7[0xd] = 0;
      puVar7[0xe] = 0;
      uVar5 = DAT_00e2b1a4;
      puVar7[10] = local_28;
      uVar3 = *param_2;
      puVar7[0xf] = uVar5;
      puVar7[0x10] = uVar3;
      puVar7[0x11] = uVar1;
      puVar7[0x12] = uVar2;
      puVar7[0x13] = uVar5;
      puVar7[0x14] = uVar3;
      puVar7[0x15] = uVar1;
      puVar7[0x16] = uVar2;
      puVar7[0x17] = uVar5;
      return CONCAT31((int3)((uint)puVar7 >> 8),1);
    }
  }
  return (uint)puVar7 & 0xffffff00;
}