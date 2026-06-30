// FUNC_NAME: EARSList::destructor
void __fastcall EARSList::destructor(undefined4 *this)
{
  int iVar1;
  int *piVar2;
  
  *this = &PTR_FUN_00e37f3c;
  if (this[0x26] != 0) {
    FUN_00505e80(this[0x26]);
    this[0x26] = 0;
  }
  // Unlink node from doubly-linked list
  *(undefined4 *)(this[0xb] + 0x28) = this[10];
  *(undefined4 *)(this[10] + 0x2c) = this[0xb];
  // Free all nodes in the list
  if (this[0xc] != this[0xe]) {
    do {
      iVar1 = this[0xc];
      if (*(int *)(iVar1 + 0x10) != 0) {
        *(int *)(*(int *)(iVar1 + 0x14) + 0x10) = *(int *)(iVar1 + 0x10);
        *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x14) = *(undefined4 *)(iVar1 + 0x14);
        *(undefined4 *)(iVar1 + 0x10) = 0;
      }
    } while (this[0xc] != this[0xe]);
  }
  // Remove from global list
  iVar1 = this[9];
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_012068e8 + 0x14);
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8;
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    this[9] = 0;
  }
  *this = &PTR_FUN_00e37f48;
  if (this[4] != 0) {
    *(undefined4 *)(this[5] + 0x10) = this[4];
    *(undefined4 *)(this[4] + 0x14) = this[5];
    this[4] = 0;
  }
  *this = &PTR_LAB_00e37304;
  return;
}