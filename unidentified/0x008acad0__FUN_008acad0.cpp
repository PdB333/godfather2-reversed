// FUNC_NAME: SomeClass::setSomeProperty
void __thiscall SomeClass::setSomeProperty(int this, undefined4 param_2)
{
  *(undefined4 *)(this + 0x90) = param_2; // +0x90: some property field
  FUN_008aada0(); // likely a notification or update method
  return;
}