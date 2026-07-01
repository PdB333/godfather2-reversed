// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  char cVar1;
  
  *this = &PTR_FUN_00d826fc;
  this[0xf] = &PTR_LAB_00d826ec;
  this[0x12] = &PTR_LAB_00d826e8;
  this[0x14] = &PTR_LAB_00d826e4;
  cVar1 = FUN_00402080(&DAT_0120e93c);
  if (cVar1 != '\0') {
    FUN_004086d0(&DAT_0120e93c);
  }
  FUN_00408310(this + 0x16);
  FUN_00408310(this + 0x18);
  this[0x14] = &PTR_LAB_00e32854;
  FUN_0046c640();
  return;
}