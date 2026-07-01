// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int thisPtr)
{
  // Call a function on a sub-object at offset +0x10
  FUN_0070b6a0(thisPtr + 0x10);
  
  // Call a virtual function via vtable at +0x4, passing two arguments from +0x8 and +0xC
  (**(code **)(thisPtr + 4))(*(undefined4 *)(thisPtr + 8), *(undefined4 *)(thisPtr + 0xc));
}