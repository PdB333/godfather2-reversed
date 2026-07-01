// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(undefined4 *thisPtr)
{
  thisPtr[1] = 0; // +0x04: some field
  FUN_009c8f10(*thisPtr); // call with first field as argument
  *thisPtr = 0; // +0x00: some pointer or handle
  thisPtr[2] = 0; // +0x08: another field
  return;
}