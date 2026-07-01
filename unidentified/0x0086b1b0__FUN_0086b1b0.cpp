// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_LAB_00d75d54;
  iVar1 = (**(code **)(*(int *)this[0x14] + 0x24))();
  if (iVar1 != 0) {
    FUN_0086b810(0);
  }
  FUN_0086aff0();
  return;
}