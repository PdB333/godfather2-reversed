// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  *this = &PTR_LAB_00d6924c;
  FUN_007ff050(0);
  FUN_0077de00(0);
  FUN_007f6420(0x49);
  FUN_007f6420(0x2d);
  FUN_007f6420(0xf);
  FUN_007f6420(0xb);
  FUN_00408310(&DAT_0112af44);
  FUN_00408310(&DAT_0112af3c);
  if (this[0x1e] != 0) {
    FUN_004daf90(this + 0x1e); // delete member at +0x78
  }
  if (this[0x1c] != 0) {
    FUN_004daf90(this + 0x1c); // delete member at +0x70
  }
  *this = &PTR_LAB_00d63090;
  if (this[0x1a] != 0) {
    FUN_004daf90(this + 0x1a); // delete member at +0x68
  }
  FUN_0080ea60();
  return;
}