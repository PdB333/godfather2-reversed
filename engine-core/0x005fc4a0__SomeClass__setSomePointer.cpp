// FUNC_NAME: SomeClass::setSomePointer
void SomeClass::setSomePointer(int *param_1, int param_2)
{
  undefined4 *edi = param_1; // unaff_EDI
  *edi = param_1;
  (**(code **)(*param_1 + 8))(); // call virtual function at vtable+8
  if (param_2 != 0) {
    int uVar1 = FUN_004265d0(param_2, *edi); // likely a copy or reference function
    edi[1] = uVar1; // store result at offset +4
    (**(code **)(*param_1 + 4))(param_2, 0); // call virtual function at vtable+4 with param_2 and 0
    (**(code **)(*param_1 + 0xc))(); // call virtual function at vtable+12
    return;
  }
  edi[1] = 0; // clear offset +4
  (**(code **)(*param_1 + 0xc))(); // call virtual function at vtable+12
  return;
}