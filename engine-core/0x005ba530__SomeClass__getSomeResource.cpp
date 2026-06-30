// FUNC_NAME: SomeClass::getSomeResource
undefined4 __fastcall SomeClass::getSomeResource(int this)
{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_005bb050(*(undefined4 *)(this + 8), in_EAX);
  if (iVar1 != 0) {
    uVar2 = FUN_005a8fe0();
    return uVar2;
  }
  return 0xffffffff;
}