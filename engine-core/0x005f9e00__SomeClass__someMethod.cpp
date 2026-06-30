// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int *param_1, int param_2)
{
  int *thisPtr;
  undefined4 uVar1;
  
  thisPtr = param_1;
  // Call virtual function at vtable+8 (likely a constructor or init)
  (**(code **)(*param_1 + 8))(param_1);
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    // Call FUN_004265d0 with param_2 and thisPtr - likely a resource/asset lookup
    uVar1 = FUN_004265d0(param_2, thisPtr);
  }
  
  // Call FUN_005fa2e0 with thisPtr and the result
  FUN_005fa2e0(thisPtr, uVar1);
  
  // Store param_1 at offset +0x8 of the object pointed to by in_EAX
  *(int **)(in_EAX + 8) = param_1;
  
  // Call virtual function at vtable+8 again
  (**(code **)(*param_1 + 8))();
  
  if (param_2 != 0) {
    // Lookup again with the stored pointer
    uVar1 = FUN_004265d0(param_2, *(undefined4 *)(in_EAX + 8));
    // Store result at offset +0xC
    *(undefined4 *)(in_EAX + 0xc) = uVar1;
    
    // Call virtual function at vtable+4 with param_2 and 0
    (**(code **)(*param_1 + 4))(param_2, 0);
    
    // Call virtual function at vtable+0xC
    (**(code **)(*param_1 + 0xc))();
    return;
  }
  
  // Store 0 at offset +0xC
  *(undefined4 *)(in_EAX + 0xc) = 0;
  
  // Call virtual function at vtable+0xC
  (**(code **)(*param_1 + 0xc))();
  return;
}