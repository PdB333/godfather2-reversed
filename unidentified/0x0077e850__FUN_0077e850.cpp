// FUNC_NAME: SomeClass::getSomeValue
uint __thiscall SomeClass::getSomeValue(int thisPtr, int *param_2)
{
  uint result;
  int local_8;
  undefined4 local_4;
  
  local_8 = *param_2;
  local_4 = *(undefined4 *)(thisPtr + 0x50); // +0x50: some member
  result = in_EAX & 0xffffff00;
  if ((local_8 != 0) && (*(int *)(thisPtr + 0x5c) != 0)) { // +0x5c: function pointer or vtable
    result = (**(code **)**(undefined4 **)(thisPtr + 0x5c))(&local_8);
  }
  return result;
}