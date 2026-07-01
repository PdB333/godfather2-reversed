// FUNC_NAME: SomeClass::handleInputEvent
void __thiscall SomeClass::handleInputEvent(int this, int param_2, uint param_3)
{
  uint uVar1;
  
  FUN_00415350(param_2, param_3);
  if (param_2 == -0x2a07d3be) {
    uVar1 = FUN_0088cfd0();
    if ((*(uint *)(this + 0x34) & (uVar1 | param_3)) == 0) {
      uVar1 = *(uint *)(this + 0x28) & 0xffffffc0;
    }
    else {
      uVar1 = thunk_FUN_0042a990(param_3);
      uVar1 = uVar1 & *(uint *)(this + 0x28);
    }
    *(uint *)(this + 0x2c) = uVar1;
    if (*(int *)(this + 0x20) != 0) {
      FUN_004df8b0(uVar1);
    }
  }
  return;
}