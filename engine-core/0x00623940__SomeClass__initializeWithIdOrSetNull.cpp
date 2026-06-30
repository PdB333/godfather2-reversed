// FUNC_NAME: SomeClass::initializeWithIdOrSetNull

void SomeClass::initializeWithIdOrSetNull(int *param_1, int param_2)
{
  int *piVar2;
  undefined4 uVar1;
  
  piVar2 = param_1;
  // Call virtual function at offset 0x08 - likely a constructor/init
  (**(code **)(*param_1 + 8))(param_1);
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    // Resolve or transform the parameter into some identifier
    uVar1 = FUN_004265d0(param_2, piVar2);
  }
  // Store the resolved value (or 0) into the object
  FUN_006240e0(piVar2, uVar1);
  // Save the object pointer at this->+0x0C (some internal list/container)
  *(int **)(in_EAX + 0xc) = param_1;
  // Call virtual function at offset 0x08 again - second phase init
  (**(code **)(*param_1 + 8))();
  if (param_2 != 0) {
    // Resolve parameter again for a secondary identifier
    uVar1 = FUN_004265d0(param_2, *(undefined4 *)(in_EAX + 0xc));
    // Store secondary identifier at this->+0x10
    *(undefined4 *)(in_EAX + 0x10) = uVar1;
    // Call virtual function at offset 0x04 - possibly a reference counter or cleanup
    (**(code **)(*param_1 + 4))(param_2, 0);
    (**(code **)(*param_1 + 0xc))();  // Call virtual at offset 0x0C - finalize
    return;
  }
  // If param_2 is null, store 0 at this->+0x10 (no secondary identifier)
  *(undefined4 *)(in_EAX + 0x10) = 0;
  (**(code **)(*param_1 + 0xc))();  // Call virtual at offset 0x0C - finalize
  return;
}