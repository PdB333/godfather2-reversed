// FUNC_NAME: SomeClass::handleSomeEvent
void __thiscall SomeClass::handleSomeEvent(int this, undefined4 param_2)
{
  int iVar1;
  
  iVar1 = FUN_00445ff0(param_2,0);
  if ((iVar1 == 0) && ((*(uint *)(this + 0xdc) >> 0x1d & 1) != 0)) {
    FUN_00445f70(param_2);
  }
  return;
}