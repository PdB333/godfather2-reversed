// FUNC_NAME: SomeClass::destructor (likely a container or resource manager)
void __fastcall SomeClass_destructor(undefined4 *this)
{
  int iVar1;
  int *piVar2;
  
  iVar1 = this[5]; // +0x14: pointer to some resource/object
  *this = &PTR_FUN_00e37e0c; // vtable pointer for base class
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_012068e8 + 0x14); // global allocation manager? +0x14 is some offset
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8; // vtable for free list node
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1; // store pointer in free list
    *piVar2 = *piVar2 + 4;
    this[5] = 0; // clear pointer
  }
  iVar1 = this[6]; // +0x18: another pointer to resource/object
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_012068e8 + 0x14);
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8;
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    this[6] = 0;
  }
  *this = &PTR_LAB_00e37304; // vtable for derived class (or final vtable)
  return;
}