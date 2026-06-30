// FUNC_NAME: SomeClass::initializeSomething
void __fastcall SomeClass::initializeSomething(int this)
{
  undefined4 uVar1;
  
  uVar1 = FUN_0060a380();
  *(undefined4 *)(this + 0x10) = uVar1;
  uVar1 = FUN_0060a2e0(&PTR_DAT_0110a36c);
  *(undefined4 *)(this + 0x14) = uVar1;
  FUN_006127d0();
  return;
}