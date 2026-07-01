// FUNC_NAME: SomeAllocator::allocateNode
int __fastcall SomeAllocator::allocateNode(int param_1)
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 uStack00000004;
  
  iVar1 = FUN_0049c9c0(); // likely allocate memory block
  if (*(int *)(DAT_0122337c + 0x84) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(DAT_0122337c + 0x84) + 0x1c); // +0x1c some field
  }
  iVar3 = FUN_004025a0(uVar2); // likely get some object/manager
  if (iVar3 == 0) {
    uStack00000004 = 0xfe16702f; // default value
  }
  else {
    uStack00000004 = *(undefined4 *)(iVar3 + 0x2c); // +0x2c some field
  }
  *(undefined4 *)(iVar1 + 4) = uStack00000004; // set field at +0x04
  uVar5 = 0;
  if (*(int *)(iVar1 + 0xc) != 0) { // +0x0c count
    piVar4 = (int *)(iVar1 + 0x10); // +0x10 array start
    do {
      *piVar4 = *piVar4 + iVar1; // adjust pointers relative to base
      uVar5 = uVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (uVar5 < *(uint *)(iVar1 + 0xc)); // loop over count
  }
  *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(param_1 + 0xc); // +0x08 copy from param_1+0x0c
  *(int *)(param_1 + 0xc) = iVar1; // link: param_1+0x0c points to new node
  return iVar1;
}