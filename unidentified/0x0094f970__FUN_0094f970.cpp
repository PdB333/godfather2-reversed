// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d8bac0; // vtable pointer
  this[0xf] = &PTR_LAB_00d8bab0; // +0x3C
  this[0x12] = &PTR_LAB_00d8baac; // +0x48
  FUN_004086d0(this + 0x14); // +0x50 - likely a sub-object destructor
  FUN_00408310(this + 0x14); // +0x50 - another sub-object cleanup
  FUN_004086d0(this + 0x16); // +0x58 - another sub-object destructor
  FUN_00408310(this + 0x16); // +0x58 - another sub-object cleanup
  if ((*(byte *)(this + 0x1a) & 2) != 0) { // +0x68 - flag check
    FUN_00939ba0(this[0x18]); // +0x60 - release a resource
    *(byte *)(this + 0x1a) = *(byte *)(this + 0x1a) & 0xfd; // clear bit 1
  }
  FUN_0046c640(); // global cleanup
  return;
}