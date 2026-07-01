// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int *piVar1;
  
  *this = &PTR_FUN_00d775c8;
  this[0xf] = &PTR_LAB_00d775b8;
  this[0x12] = &PTR_LAB_00d775b4;
  this[0x14] = &PTR_LAB_00d775b0;
  this[0x15] = &PTR_LAB_00d77550;
  this[0x16] = &PTR_LAB_00d774e8;
  FUN_004086d0(&DAT_012069c4);
  if ((this[0x70] != 0) && (*(char *)(this + 0x71) != '\0')) {
    piVar1 = (int *)(this[0x70] + 0x18);
    *piVar1 = *piVar1 + -1;
    *(undefined1 *)(this + 0x71) = 0;
  }
  FUN_0046ea20();
  return;
}