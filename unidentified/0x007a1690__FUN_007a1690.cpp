// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int this, undefined4 param_2)
{
  // Call to FUN_004a9320 with param_2 and this+0x10
  FUN_004a9320(param_2,this + 0x10);
  // Call to FUN_0064bb50 with the byte at this+0x18
  FUN_0064bb50(*(undefined1 *)(this + 0x18));
  return;
}