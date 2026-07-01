// FUNC_NAME: SomeClass::getSomeProperty
undefined4 __fastcall SomeClass::getSomeProperty(int this)
{
  int iVar1;
  
  iVar1 = FUN_006b0ee0(*(undefined4 *)(this + 0x58));
  if (iVar1 != 0) {
    return *(undefined4 *)(iVar1 + 0x48);
  }
  return 0;
}