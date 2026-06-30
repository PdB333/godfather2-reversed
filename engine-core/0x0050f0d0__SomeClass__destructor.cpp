// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass *this)
{
  byte bVar1;
  int iVar2;
  int *piVar3;
  
  bVar1 = *(byte *)(this + 0x1c); // +0x1c: some state/type byte
  *this = &PTR_FUN_00e380ec; // vtable pointer
  if (bVar1 != 0) {
    if (bVar1 < 3) goto LAB_0050f1af;
    if (bVar1 == 6) {
      iVar2 = *(int *)(this + 0x50); // +0x50: some resource pointer
      if (iVar2 != 0) {
        FUN_004bfcf0(); // some cleanup function
        piVar3 = (int *)FUN_009c8f80(); // get allocator
        (**(code **)(*piVar3 + 4))(iVar2, 0xa0); // free with size 0xa0
      }
      goto LAB_0050f1af;
    }
  }
  iVar2 = *(int *)(this + 0x5c); // +0x5c: pointer to something
  if (iVar2 != 0) {
    piVar3 = (int *)(DAT_012068e8 + 0x14); // global list head
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8; // list node sentinel
    *piVar3 = *piVar3 + 4;
    *(int *)*piVar3 = iVar2;
    *piVar3 = *piVar3 + 4;
    *(int *)(this + 0x5c) = 0;
  }
  iVar2 = *(int *)(this + 0x60); // +0x60: another pointer
  if (iVar2 != 0) {
    piVar3 = (int *)(DAT_012068e8 + 0x14);
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8;
    *piVar3 = *piVar3 + 4;
    *(int *)*piVar3 = iVar2;
    *piVar3 = *piVar3 + 4;
    *(int *)(this + 0x60) = 0;
  }
  iVar2 = *(int *)(this + 0x64); // +0x64: another pointer
  if (iVar2 != 0) {
    piVar3 = (int *)(DAT_012068e8 + 0x14);
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8;
    *piVar3 = *piVar3 + 4;
    *(int *)*piVar3 = iVar2;
    *piVar3 = *piVar3 + 4;
    *(int *)(this + 0x64) = 0;
  }
  iVar2 = *(int *)(this + 0x68); // +0x68: another pointer
  if (iVar2 != 0) {
    piVar3 = (int *)(DAT_012068e8 + 0x14);
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8;
    *piVar3 = *piVar3 + 4;
    *(int *)*piVar3 = iVar2;
    *piVar3 = *piVar3 + 4;
    *(int *)(this + 0x68) = 0;
  }
LAB_0050f1af:
  iVar2 = *(int *)(this + 0x58); // +0x58: another resource pointer
  if (iVar2 != 0) {
    if (DAT_0120ec84 != (code *)0x0) {
      (*DAT_0120ec84)(iVar2); // custom destructor callback
    }
    piVar3 = (int *)FUN_009c8f80(); // get allocator
    (**(code **)(*piVar3 + 4))(iVar2, 0xb0); // free with size 0xb0
  }
  *this = &PTR_LAB_00e37304; // final vtable pointer
  return;
}