// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(undefined4 *this, int param_2)
{
  int iVar1;
  
  *this = &PTR_LAB_00d75180; // vtable pointer
  this[2] = 0xbadbadba; // +0x08: magic constant
  this[3] = 0xbeefbeef; // +0x0C: magic constant
  this[4] = 0xeac15a55; // +0x10: magic constant
  this[5] = 0x91100911; // +0x14: magic constant
  this[6] = 0;          // +0x18: initialize to zero
  *(undefined1 *)(this + 7) = 0; // +0x1C: byte field initialized to zero
  this[1] = **(undefined4 **)(param_2 + 4); // +0x04: copy from param_2+4
  iVar1 = *(int *)(param_2 + 4);
  this[2] = *(undefined4 *)(iVar1 + 0xc);  // +0x08: copy from offset 0x0C
  this[3] = *(undefined4 *)(iVar1 + 0x10); // +0x0C: copy from offset 0x10
  this[4] = *(undefined4 *)(iVar1 + 0x14); // +0x10: copy from offset 0x14
  this[5] = *(undefined4 *)(iVar1 + 0x18); // +0x14: copy from offset 0x18
  return;
}