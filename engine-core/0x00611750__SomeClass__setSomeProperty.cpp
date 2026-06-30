// FUNC_NAME: SomeClass::setSomeProperty
void __thiscall SomeClass::setSomeProperty(int this, undefined4 param_2)
{
  *(undefined4 *)(this + 0x100) = param_2; // +0x100: some property value
  if ((DAT_012058e8 == this) && (*(int *)(this + 0xfc) != 0)) { // +0xfc: some flag or pointer
    FUN_006063b0(); // likely a callback or notification function
  }
  return;
}