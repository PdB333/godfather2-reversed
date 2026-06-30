// FUNC_NAME: SomeClass::initArrayOrSomething
void FUN_0065df10(void)
{
  longlong lVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int *this; // unaff_ESI
  uint elementCount; // unaff_EDI

  // +0x0C: some field (offset 12 bytes from this)
  this[3] = DAT_00e35654;
  // +0x04: some field
  this[1] = 0;
  // +0x08: some field
  this[2] = elementCount;
  // +0x10: some field
  this[4] = 0;

  // Allocate memory for an array of pointers? (0xC = 12 bytes)
  iVar2 = FUN_009c8e50(0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    // Allocate memory for elementCount+1 pointers (each 4 bytes)
    lVar1 = (ulonglong)(elementCount + 1) * 4;
    uVar3 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
    *(undefined4 *)(iVar2 + 8) = uVar3;
  }
  // +0x00: pointer to allocated structure
  *this = iVar2;

  // Initialize all elements to 0
  uVar4 = 0;
  do {
    *(undefined4 *)(*(int *)(*this + 8) + uVar4 * 4) = 0;
    uVar4 = uVar4 + 1;
  } while (uVar4 <= elementCount);

  // Allocate another array of elementCount+1 ints
  lVar1 = (ulonglong)(elementCount + 1) * 4;
  iVar2 = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  // +0x14: pointer to second array
  this[5] = iVar2;
  return;
}