// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int param_1)
{
  int iVar1;
  int local_4;
  
  local_4 = param_1;
  FUN_0088f000(&local_4,&stack0x00000004);
  iVar1 = local_4;
  *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + -1;
  FUN_00ab3c50(local_4);
  FUN_00ab4010(iVar1,param_1 + 100);
  FUN_009c8f10(iVar1);
  return;
}