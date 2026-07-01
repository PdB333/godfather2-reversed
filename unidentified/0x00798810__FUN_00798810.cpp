// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int *this, undefined4 param_2)
{
  int vtable;
  undefined4 someValue;
  
  vtable = *this;
  someValue = FUN_00481620(); // Likely returns a game state or time value
  (**(code **)(vtable + 0x300))(param_2, someValue); // Virtual call at vtable offset 0x300 (768)
  return;
}