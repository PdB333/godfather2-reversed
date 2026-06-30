// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(undefined4 *param_1)
{
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  
  puVar1 = (undefined4 *)((int)param_1 + 0x100);
  uVar3 = 0x369ac561;
  param_1 = (undefined4 *)0x0;
  cVar2 = (**(code **)(*(int *)*puVar1 + 0x10))(0x369ac561,&param_1);
  if (cVar2 != '\0') {
    *param_1 = uVar3;
    return;
  }
  *param_1 = uVar3;
  return;
}