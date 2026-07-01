// FUNC_NAME: SomeClass::setSomeProperty
void __thiscall SomeClass::setSomeProperty(int this, undefined4 param_2)
{
  FUN_004a93d0(param_2, this + 8);  // Copy param_2 to offset +0x8
  FUN_0064b9e0(0x20, &param_2);    // Some operation with size 0x20
  *(undefined4 *)(this + 0x1c) = param_2;  // Store param_2 at offset +0x1c
  return;
}