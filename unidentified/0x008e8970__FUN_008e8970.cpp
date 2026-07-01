// FUNC_NAME: SomeClass::handleSomeEvent
void __thiscall SomeClass::handleSomeEvent(int this, int *param_2)
{
  int iVar1;
  
  if ((*param_2 != DAT_0120e93c) && (*param_2 != DAT_012067dc)) {
    iVar1 = (**(code **)(*(int *)(this + -0x3c) + 0x15c))();
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x3c) + 4))(param_2);
    }
    return;
  }
  FUN_0046efc0(param_2);
  return;
}