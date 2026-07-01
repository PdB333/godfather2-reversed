// FUNC_NAME: SomeClass::checkAndDoSomething
void SomeClass::checkAndDoSomething(int param_1)
{
  // Check if the parameter is non-null and the value at offset +0x180 is less than 0x19 (25)
  if ((param_1 != 0) && (*(uint *)(param_1 + 0x180) < 0x19)) {
    // Call the function at 0x008dd630
    FUN_008dd630();
    return;
  }
  return;
}