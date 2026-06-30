// FUNC_NAME: SomeClass::setSomeFlags
void __thiscall setSomeFlags(void *this, undefined4 param_1)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  // Call virtual function at vtable[0] with a pointer to a struct containing flags (2, 0x10, 0)
  (*(code *)**(undefined4 **)this)(param_1, &local_c);
  return;
}