// FUNC_NAME: SomeClass::resetOrConstructor
void __fastcall SomeClass::resetOrConstructor(undefined4 *this)
{
  this[1] = 0; // +0x04: some field, likely a pointer or handle
  FUN_009c8f10(*this); // call to some initialization/cleanup function with first field as argument
  *this = 0; // +0x00: reset first field (likely a pointer or handle)
  this[2] = 0; // +0x08: reset third field
  return;
}