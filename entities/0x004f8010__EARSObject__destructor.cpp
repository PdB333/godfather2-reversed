// FUNC_NAME: EARSObject::destructor
void EARSObject::destructor(void)
{
  int iVar1;
  int *piVar2;
  undefined4 *this;
  
  *this = &PTR_LAB_00e37940;
  FUN_004ebba0();
  FUN_004ebba0();
  FUN_004ebba0();
  iVar1 = this[0xb]; // +0x2C - some member pointer
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x20) != 0) {
      piVar2 = (int *)(*(int *)(iVar1 + 0x20) + 4);
      *piVar2 = *piVar2 + -1;
      if ((*(int **)(iVar1 + 0x20))[1] == 0) {
        (**(code **)(**(int **)(iVar1 + 0x20) + 4))();
      }
      *(undefined4 *)(iVar1 + 0x20) = 0;
    }
    *(undefined4 *)(iVar1 + 0x20) = 0;
    if ((this[10] & 0x100) == 0) { // +0x28 flags check
      iVar1 = this[0xb]; // +0x2C
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x200000;
      FUN_0051d6b0();
      if (*(undefined4 **)(iVar1 + 8) != (undefined4 *)0x0) {
        **(undefined4 **)(iVar1 + 8) = 0;
        *(undefined4 *)(iVar1 + 8) = 0;
      }
    }
    else {
      FUN_0051b340();
    }
  }
  iVar1 = this[0xd]; // +0x34 - another member
  if (iVar1 != 0) {
    FUN_004f8530(iVar1);
    FUN_009c8eb0(iVar1);
  }
  *this = &PTR_FUN_00e37110;
  iVar1 = this[4]; // +0x10
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8;
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    this[4] = 0; // +0x10
    this[5] = 0; // +0x14
  }
  return;
}