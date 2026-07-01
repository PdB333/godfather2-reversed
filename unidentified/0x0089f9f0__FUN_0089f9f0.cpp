// FUNC_NAME: SomeClass::initOrResetSomething
int __fastcall SomeClass::initOrResetSomething(int this)
{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(this + 8);
  iVar2 = 3;
  do {
    puVar1[-2] = 0;
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 3;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  FUN_0089eb80();
  return this;
}