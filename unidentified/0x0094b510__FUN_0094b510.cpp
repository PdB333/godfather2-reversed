// FUNC_NAME: SomeClass::handleSomeAction
void SomeClass::handleSomeAction(int param_1, int param_2)
{
  int result;
  
  result = SomeOtherClass::someCheck(&param_1);
  if (-1 < result) {
    SomeOtherClass::someAction(param_2);
  }
  return;
}