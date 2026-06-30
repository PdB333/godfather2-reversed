// FUNC_NAME: SomeClass::destructor
void SomeClass::destructor(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00e3f470;
  FUN_005e1e50();
  if (this[0x5ce] != 0) {
    FUN_009c8f10(this[0x5ce]); // +0x1738 - likely a pointer to a sub-object
  }
  iVar1 = 4;
  do {
    FUN_005e8260(); // called 5 times, possibly releasing resources
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  *this = &PTR_LAB_00e3f474;
  DAT_0122350c = 0;
  return;
}