// FUNC_NAME: someClass::someMethod
void someClass::someMethod(void)
{
  int loopCount;
  
  loopCount = 2;
  do {
    // Call to FUN_004df710 - likely a helper or initialization function
    FUN_004df710();
    loopCount = loopCount + -1;
  } while (loopCount != 0);
  return;
}