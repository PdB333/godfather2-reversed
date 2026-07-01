// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass *this)
{
  int *piVar1;
  
  *this = &PTR_LAB_00d6e84c;
  FUN_007c5d70();
  FUN_004ac600(0);
  if ((*(byte *)(this + 0x1d) & 1) != 0) {
    piVar1 = (int *)FUN_007ab150();
    (**(code **)(*piVar1 + 4))(1);
  }
  piVar1 = (int *)FUN_007ab130();
  (**(code **)(*piVar1 + 4))(this[0x1e]); // +0x78
  if (this[0x23] != 0) { // +0x8C
    FUN_004daf90(this + 0x23);
  }
  if (this[0x21] != 0) { // +0x84
    FUN_004daf90(this + 0x21);
  }
  if (this[0x1f] != 0) { // +0x7C
    FUN_004daf90(this + 0x1f);
  }
  *this = &PTR_LAB_00d6b95c;
  FUN_0080ea60();
  return;
}