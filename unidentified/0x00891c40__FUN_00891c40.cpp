// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(undefined4 *thisPtr)
{
  thisPtr[1] = 0; // +0x04: some field, likely a pointer or counter
  FUN_009c8f10(*thisPtr); // call with first field (thisPtr[0]) as argument
  *thisPtr = 0; // +0x00: reset first field to null/zero
  thisPtr[2] = 0; // +0x08: another field reset
  return;
}