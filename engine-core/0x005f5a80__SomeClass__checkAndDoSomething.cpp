// FUNC_NAME: SomeClass::checkAndDoSomething
void SomeClass::checkAndDoSomething(int *param_1)
{
  // Check if the value pointed to by param_1 matches a global constant (DAT_012069c4)
  if (*param_1 == DAT_012069c4) {
    // If match, call function with argument 200 (likely a delay or timeout value)
    FUN_005f7920(200);
    // Then call another function (likely a reset or initialization routine)
    FUN_005fb030();
  }
  return;
}