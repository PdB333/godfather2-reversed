// FUNC_NAME: SomeClass::setSomething
void __thiscall SomeClass::setSomething(int this, undefined4 param_2)
{
  undefined4 uVar1;
  uint uVar2;
  
  // Store the parameter at offset +0x70 (likely a member variable)
  *(char *)(this + 0x70) = (char)param_2;
  
  // Call a function that returns some value (possibly a time or state)
  uVar1 = FUN_00977420();
  
  uVar2 = 0;
  // Check if there's a count at offset +0x64 (100 decimal)
  if (*(int *)(this + 100) != 0) {
    do {
      // Call a function for each iteration, passing the stored value and the result
      FUN_0094ae10(param_2, uVar1);
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 100));
  }
  return;
}