// FUNC_NAME: SomeClass::resetOrInit
void __fastcall SomeClass::resetOrInit(undefined4 *this)
{
  this[1] = 0;          // +0x04: some field, likely a pointer or handle
  FUN_009c8f10(this[0]); // call to some initialization/cleanup function with the first field
  this[0] = 0;          // +0x00: reset first field to null/zero
  this[2] = 0;          // +0x08: another field reset
  return;
}