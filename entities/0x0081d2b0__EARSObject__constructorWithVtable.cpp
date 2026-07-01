// FUNC_NAME: EARSObject::constructorWithVtable
int __thiscall EARSObject::constructorWithVtable(int thisPtr, int *vtablePtr, int param3)
{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = vtablePtr;
  // Call vtable function at offset 8 (likely init or pre-constructor)
  (**(code **)(*vtablePtr + 8))(vtablePtr);
  
  if (param3 == 0) {
    uVar1 = 0;
  }
  else {
    // FUN_004265d0 appears to be a reference counting or copy function
    uVar1 = FUN_004265d0(param3, piVar2);
  }
  
  // FUN_0081cac0 likely sets up internal state
  FUN_0081cac0(piVar2, uVar1);
  
  // Store vtable pointer at +0x10
  *(int **)(thisPtr + 0x10) = vtablePtr;
  
  // Call vtable function at offset 8 again (second init pass)
  (**(code **)(*vtablePtr + 8))();
  
  if (param3 != 0) {
    // Copy/reference param3 into +0x14
    uVar1 = FUN_004265d0(param3, *(undefined4 *)(thisPtr + 0x10));
    *(undefined4 *)(thisPtr + 0x14) = uVar1;
    
    // Call vtable function at offset 4 (likely attach or set parent)
    (**(code **)(*vtablePtr + 4))(param3, 0);
    
    // Call vtable function at offset 0xC (finalize construction)
    (**(code **)(*vtablePtr + 0xc))();
    return thisPtr;
  }
  
  // No param3: set +0x14 to 0
  *(undefined4 *)(thisPtr + 0x14) = 0;
  
  // Call vtable function at offset 0xC (finalize construction)
  (**(code **)(*vtablePtr + 0xc))();
  return thisPtr;
}