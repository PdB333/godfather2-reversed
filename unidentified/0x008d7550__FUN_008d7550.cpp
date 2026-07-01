// FUNC_NAME: SomeClass::resetSomeData
void __fastcall SomeClass::resetSomeData(int this)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar1 = _DAT_00d5c458; // global default value (likely 0 or -1)
  uVar5 = 0;
  *(undefined4 *)(this + 0x20) = _DAT_00d5c458; // +0x20: some field
  if (*(int *)(this + 0x30) != 0) { // +0x30: count of first array
    iVar4 = 0;
    do {
      puVar2 = (undefined4 *)(*(int *)(this + 0x2c) + iVar4 + 0xc); // +0x2c: pointer to first array, each element size 0x2c, offset 0xc within element
      iVar3 = 2;
      do {
        *puVar2 = uVar1;
        puVar2 = puVar2 + 5; // advance by 5 * 4 = 20 bytes (0x14)
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x2c; // next element
    } while (uVar5 < *(uint *)(this + 0x30));
  }
  uVar5 = 0;
  if (*(int *)(this + 0x3c) != 0) { // +0x3c: count of second array
    iVar4 = 0;
    do {
      *(undefined4 *)(*(int *)(this + 0x38) + 0xc + iVar4) = uVar1; // +0x38: pointer to second array, each element size 0x18, offset 0xc within element
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x18; // next element
    } while (uVar5 < *(uint *)(this + 0x3c));
  }
  *(undefined4 *)(this + 0x4c) = uVar1; // +0x4c: some field
  *(undefined4 *)(this + 0x60) = uVar1; // +0x60: some field
  *(undefined4 *)(this + 0x74) = uVar1; // +0x74: some field
  *(undefined4 *)(this + 0x88) = uVar1; // +0x88: some field
  *(undefined4 *)(this + 0x9c) = uVar1; // +0x9c: some field
  return;
}