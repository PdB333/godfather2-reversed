// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(undefined4 param_1, undefined4 param_2)
{
  // Call a virtual function at offset +0x4 of the object pointed to by DAT_01194538
  // This is likely a member function call on a singleton or global object
  (**(code **)(*DAT_01194538 + 4))(param_2, 0);
  return;
}