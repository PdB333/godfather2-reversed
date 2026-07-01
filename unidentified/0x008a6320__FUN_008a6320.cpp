// FUNC_NAME: someClass::someMethod
int someClass::someMethod(int param_1)
{
  int local_4;
  
  someOtherMethod(param_1, &local_4, &param_1);
  return local_4 + param_1;
}