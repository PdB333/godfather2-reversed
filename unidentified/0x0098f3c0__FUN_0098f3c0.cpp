// FUNC_NAME: SomeClass::resetOrInitialize
void __fastcall SomeClass::resetOrInitialize(undefined4 *this)
{
  this[1] = 0;          // +0x04: some field, likely a flag or counter
  FUN_009c8f10(*this);  // call to some initialization or cleanup function with first field as argument
  *this = 0;            // +0x00: first field (pointer or handle) set to null
  this[2] = 0;          // +0x08: another field set to zero
  return;
}