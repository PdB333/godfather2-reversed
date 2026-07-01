// FUNC_NAME: someClass::someMethod
void someClass::someMethod(void)
{
  int counter;
  
  counter = 2;
  do {
    // Call the function at 0x008d5df0 twice
    FUN_008d5df0();
    counter = counter + -1;
  } while (counter != 0);
  return;
}