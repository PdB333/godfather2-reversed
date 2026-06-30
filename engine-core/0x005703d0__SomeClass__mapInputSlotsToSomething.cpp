// FUNC_NAME: SomeClass::mapInputSlotsToSomething
void FUN_005703d0(int param_1)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  int unaff_EDI;
  
  uVar3 = 0;
  if (*(int *)(param_1 + 0x38) != 0) {
    do {
      // +0x70: some table pointer, +0x74: short index into table
      // +0x1c: offset within table entry, +0x14: base offset for data
      iVar1 = *(int *)(*(int *)(*(int *)(unaff_EDI + 0x70) + 0x1c) + 0x14 +
                      *(short *)(unaff_EDI + 0x74) * 0x18);
      // param_1 + 0x60: array of 8-byte entries (likely controller slot data)
      // FUN_005828a0: lookup function returning index or -1
      iVar2 = FUN_005828a0(*(undefined4 *)(*(int *)(param_1 + 0x60) + uVar3 * 8), iVar1);
      if ((iVar2 != -1) && (iVar1 = *(int *)(iVar1 + 0x10 + iVar2 * 0x14), -1 < iVar1)) {
        // +0xb4: offset to store mapping result
        *(char *)(iVar1 + *(int *)(unaff_EDI + 0xb4)) = (char)uVar3;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x38));
  }
  return;
}