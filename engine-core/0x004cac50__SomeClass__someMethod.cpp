// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int *param_1, int param_2)
{
  int *thisPtr;
  int result;
  
  thisPtr = param_1;
  // Call virtual function at vtable+8 (likely a base class method)
  (**(code **)(*param_1 + 8))(param_1);
  if (param_2 == 0) {
    result = 0;
  }
  else {
    // Call FUN_004265d0 with param_2 and thisPtr
    result = FUN_004265d0(param_2, thisPtr);
  }
  // Call FUN_004cae60 with thisPtr and result
  FUN_004cae60(thisPtr, result);
  // Store param_1 at offset +0x0C in the object pointed to by in_EAX
  *(int **)(in_EAX + 0xc) = param_1;
  // Call virtual function at vtable+8 again
  (**(code **)(*param_1 + 8))();
  if (param_2 != 0) {
    // Call FUN_004265d0 with param_2 and the value at offset +0x0C
    result = FUN_004265d0(param_2, *(undefined4 *)(in_EAX + 0xc));
    // Store result at offset +0x10
    *(undefined4 *)(in_EAX + 0x10) = result;
    // Call virtual function at vtable+4 with param_2 and 0
    (**(code **)(*param_1 + 4))(param_2, 0);
    // Call virtual function at vtable+0xC
    (**(code **)(*param_1 + 0xc))();
    return;
  }
  // Store 0 at offset +0x10
  *(undefined4 *)(in_EAX + 0x10) = 0;
  // Call virtual function at vtable+0xC
  (**(code **)(*param_1 + 0xc))();
  return;
}