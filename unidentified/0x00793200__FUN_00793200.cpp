// FUNC_NAME: SomeClass::findEmptySlotOrCreate
undefined4 __thiscall FUN_00793200(int this, undefined4 param_2)
{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  uVar2 = _rand();
  iVar5 = 0;
  // Loop to find an empty slot in an array of 4 entries (each 0x1c bytes) starting at offset +0x50
  // Checks if first 4 ints (offsets 0, 4, 8, 0xc) are all zero
  while ((((uVar4 = iVar5 + (uVar2 & 0x80000003) & 3, iVar1 = this + 0x50 + uVar4 * 0x1c,
           *(int *)(this + 0x50 + uVar4 * 0x1c) == 0 && (*(int *)(iVar1 + 4) == 0)) &&
          (*(int *)(iVar1 + 8) == 0)) && (*(int *)(iVar1 + 0xc) == 0))) {
    iVar5 = iVar5 + 1;
    if (3 < iVar5) {
      return 0; // No empty slot found after trying all 4
    }
  }
  // Found an empty slot, call function to initialize it
  uVar3 = FUN_007930f0(iVar5 + (uVar2 & 0x80000003) & 3, param_2);
  return uVar3;
}