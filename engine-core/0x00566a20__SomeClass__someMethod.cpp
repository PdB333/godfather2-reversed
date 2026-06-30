// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int param_1)
{
  // Set field at offset +0x10 to 1 (likely a state flag or mode indicator)
  *(int *)(param_1 + 0x10) = 1;
  
  // Call virtual function at vtable index 0x38 (0x38 / 4 = 14th virtual method)
  // This is an indirect call through the vtable pointer stored at param_1 + 0xC
  // The vtable pointer points to the object's class vtable
  (*(void (__thiscall **)(int))(*(int *)(*(int *)(param_1 + 0xC)) + 0x38))(param_1);
}