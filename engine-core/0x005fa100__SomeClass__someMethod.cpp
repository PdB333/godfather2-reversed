// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int *param_1, int param_2)
{
  int *piVar2;
  undefined4 uVar1;
  
  piVar2 = param_1;
  (**(code **)(*param_1 + 8))(param_1); // Call virtual function at vtable+8
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(param_2, piVar2); // Some conversion/creation function
  }
  FUN_005fa360(piVar2, uVar1); // Another helper function
  *(int **)(in_EAX + 8) = param_1; // Store param_1 at offset +0x8
  (**(code **)(*param_1 + 8))(); // Call virtual function at vtable+8 again
  if (param_2 != 0) {
    uVar1 = FUN_004265d0(param_2, *(undefined4 *)(in_EAX + 8)); // Re-convert with stored pointer
    *(undefined4 *)(in_EAX + 0xc) = uVar1; // Store result at offset +0xC
    (**(code **)(*param_1 + 4))(param_2, 0); // Call virtual function at vtable+4 with param_2 and 0
    (**(code **)(*param_1 + 0xc))(); // Call virtual function at vtable+0xC
    return;
  }
  *(undefined4 *)(in_EAX + 0xc) = 0; // Set offset +0xC to 0
  (**(code **)(*param_1 + 0xc))(); // Call virtual function at vtable+0xC
  return;
}