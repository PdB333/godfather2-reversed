// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  undefined4 *puVar1;
  
  *this = &PTR_FUN_00d81f50; // vtable pointer
  this[0xf] = &PTR_LAB_00d81f40; // +0x3C
  this[0x12] = &PTR_LAB_00d81f3c; // +0x48
  FUN_004086d0(&DAT_012069c4); // likely release/delete some resource
  puVar1 = this + 0x1a; // +0x68
  FUN_004086d0(puVar1);
  FUN_00408310(puVar1); // likely clear/zero memory
  FUN_004086d0(puVar1);
  FUN_00408310(puVar1);
  FUN_004086d0(this + 0x1e); // +0x78
  FUN_00408310(this + 0x1e);
  FUN_00408310(this + 0x20); // +0x80
  FUN_00408310(this + 0x22); // +0x88
  if (this[0x18] != 0) { // +0x60
    FUN_004daf90(this + 0x18); // likely delete pointer at +0x60
  }
  FUN_0046c640(); // some global cleanup
  return;
}