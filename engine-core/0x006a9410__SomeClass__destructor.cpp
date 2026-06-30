// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d5d94c;
  this[0xf] = &PTR_LAB_00d5d93c;
  this[0x12] = &PTR_LAB_00d5d938;
  FUN_004086d0(this + 0x14);
  FUN_00408310(this + 0x14);
  FUN_004086d0(this + 0x16);
  FUN_00408310(this + 0x16);
  FUN_004086d0(&DAT_012069c4);
  FUN_004086d0(&DAT_0120e93c);
  FUN_004086d0(this + 0x18);
  FUN_00408310(this + 0x18);
  FUN_004086d0(this + 0x1a);
  FUN_00408310(this + 0x1a);
  if (this[0x22] != 0) {
    FUN_005e6660(this[0x22]);
    this[0x22] = 0;
  }
  if (this[0x28] != 0) {
    FUN_005e6660(this[0x28]);
    this[0x28] = 0;
  }
  FUN_0046c640();
  return;
}