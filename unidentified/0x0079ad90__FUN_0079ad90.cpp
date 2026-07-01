// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(undefined4 *thisPtr)
{
  thisPtr[1] = 0; // +0x04: some field, likely a counter or flag
  FUN_009c8f10(*thisPtr); // call with the value at +0x00
  *thisPtr = 0; // +0x00: reset pointer or handle
  thisPtr[2] = 0; // +0x08: another field, likely a pointer or flag
  return;
}