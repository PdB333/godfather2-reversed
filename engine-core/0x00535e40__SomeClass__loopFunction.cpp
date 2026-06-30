// FUNC_NAME: SomeClass::loopFunction
void SomeClass::loopFunction(void)
{
  int count = in_EAX;
  
  if (0 < count) {
    do {
      // Call the inner function repeatedly
      innerFunction();
      count = count + -1;
    } while (count != 0);
  }
  return;
}