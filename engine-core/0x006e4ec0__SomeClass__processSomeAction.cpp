// FUNC_NAME: SomeClass::processSomeAction
void SomeClass::processSomeAction(int param_1)
{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  int unaff_ESI;
  
  iVar2 = param_1;
  puVar1 = (undefined4 *)(param_1 + 0x100); // +0x100: pointer to some object/interface
  param_1 = 0;
  cVar3 = (**(code **)(*(int *)*puVar1 + 0x10))(0x383225a1,&param_1); // vtable call at offset 0x10, likely a method like getSomeValue
  if ((cVar3 != '\0') && (unaff_ESI != 0)) {
    FUN_006e3e50(iVar2,param_1,unaff_ESI + 0x28b8); // call to process with parameters
  }
  return;
}