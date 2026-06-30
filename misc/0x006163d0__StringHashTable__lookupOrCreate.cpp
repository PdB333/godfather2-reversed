// FUNC_NAME: StringHashTable::lookupOrCreate
uint * StringHashTable::lookupOrCreate(void)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  byte *unaff_ESI;
  
  if (unaff_ESI == (byte *)0x0) {
    return (uint *)0x0;
  }
  uVar3 = 0;
  bVar1 = *unaff_ESI;
  while (bVar1 != 0) {
    unaff_ESI = unaff_ESI + 1;
    uVar3 = uVar3 * 0x1003f + (uint)bVar1;
    bVar1 = *unaff_ESI;
  }
  puVar2 = *(uint **)(DAT_01205960 + (uVar3 & 0xff) * 4);
  if (puVar2 != (uint *)0x0) {
    do {
      if (*puVar2 == uVar3) break;
      puVar2 = (uint *)puVar2[1];
    } while (puVar2 != (uint *)0x0);
    if (puVar2 != (uint *)0x0) {
      return puVar2;
    }
  }
  puVar2 = (uint *)FUN_006162e0();
  return puVar2;
}