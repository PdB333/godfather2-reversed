// FUNC_NAME: SomeClass::registerEventCallback
void __fastcall SomeClass::registerEventCallback(int param_1)
{
  FUN_0096b6e0(); // likely base class constructor or initialization
  if (param_1 != 0) {
    FUN_005c0d50(param_1 + 0x14, &LAB_00963f20, 0); // register callback with offset +0x14 (event handler pointer)
    return;
  }
  FUN_005c0d50(0, &LAB_00963f20, 0); // register callback with null context
  return;
}