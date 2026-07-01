// FUNC_NAME: SomeClass::updateSomeFlagOrState
void __fastcall SomeClass::updateSomeFlagOrState(undefined4 *this)
{
  int iVar1;
  
  if (((*(byte *)((int)this + 0x11e) & 1) == 0) && ((&DAT_00e56aa0)[this[1] * 0x2c] != '\0'))
  {
    if (DAT_0112a680 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = DAT_0112a680 + 4;
    }
    FUN_005c0d50(iVar1,&LAB_0094a200,*this);
    FUN_005c0d30();
    return;
  }
  return;
}